/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>


// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
// in which case, set this #define pin to 0!
#define TFT_DC     8

#define  SD_CS 4

#define BUFFPIXEL 20

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


uint16_t read16(File f) {
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

uint32_t read32(File f) {
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}

float p = 3.1415926;

void tftPrintTest() ;

void testlines(uint16_t color) ;

void testfastlines(uint16_t color1, uint16_t color2) ;

void testdrawrects(uint16_t color) ;

void testfillrects(uint16_t color1, uint16_t color2) ;

void testfillcircles(uint8_t radius, uint16_t color) ;

void testdrawcircles(uint8_t radius, uint16_t color) ;

void testroundrects() ;

void testtriangles() ;

void mediabuttons() ;

void bmpDraw(char *filename, uint8_t x, uint8_t y) {


    File     bmpFile;
    int      bmpWidth, bmpHeight;   // W+H in pixels
    uint8_t  bmpDepth;              // Bit depth (currently must be 24)
    uint32_t bmpImageoffset;        // Start of image data in file
    uint32_t rowSize;               // Not always = bmpWidth; may have padding
    uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
    uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
    boolean  goodBmp = false;       // Set to true on valid header parse
    boolean  flip    = true;        // BMP is stored bottom-to-top
    int      w, h, row, col;
    uint8_t  r, g, b;
    uint32_t pos = 0, startTime = millis();

    if((x >= tft.width()) || (y >= tft.height())) return;

    Serial.println();
    Serial.print("Loading image '");
    Serial.print(filename);
    Serial.println('\'');

    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) == NULL) {
        Serial.print("File not found");
        return;
    }

    // Parse BMP header
    if(read16(bmpFile) == 0x4D42) { // BMP signature
        Serial.print("File size: "); Serial.println(read32(bmpFile));
        (void)read32(bmpFile); // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        Serial.print("Image Offset: "); Serial.println(bmpImageoffset, DEC);
        // Read DIB header
        Serial.print("Header size: "); Serial.println(read32(bmpFile));
        bmpWidth  = read32(bmpFile);
        bmpHeight = read32(bmpFile);
        if(read16(bmpFile) == 1) { // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            Serial.print("Bit Depth: "); Serial.println(bmpDepth);
            if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

                goodBmp = true; // Supported BMP format -- proceed!
                Serial.print("Image size: ");
                Serial.print(bmpWidth);
                Serial.print('x');
                Serial.println(bmpHeight);

                // BMP rows are padded (if needed) to 4-byte boundary
                rowSize = (bmpWidth * 3 + 3) & ~3;

                // If bmpHeight is negative, image is in top-down order.
                // This is not canon but has been observed in the wild.
                if(bmpHeight < 0) {
                    bmpHeight = -bmpHeight;
                    flip      = false;
                }

                // Crop area to be loaded
                w = bmpWidth;
                h = bmpHeight;
                if((x+w-1) >= tft.width())  w = tft.width()  - x;
                if((y+h-1) >= tft.height()) h = tft.height() - y;

                // Set TFT address window to clipped image bounds
                tft.setAddrWindow(x, y, x+w-1, y+h-1);

                for (row=0; row<h; row++) { // For each scanline...

                    // Seek to start of scan line.  It might seem labor-
                    // intensive to be doing this on every line, but this
                    // method covers a lot of gritty details like cropping
                    // and scanline padding.  Also, the seek only takes
                    // place if the file position actually needs to change
                    // (avoids a lot of cluster math in SD library).
                    if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
                        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
                    else     // Bitmap is stored top-to-bottom
                        pos = bmpImageoffset + row * rowSize;
                    if(bmpFile.position() != pos) { // Need seek?
                        bmpFile.seek(pos);
                        buffidx = sizeof(sdbuffer); // Force buffer reload
                    }

                    for (col=0; col<w; col++) { // For each pixel...
                        // Time to read more pixel data?
                        if (buffidx >= sizeof(sdbuffer)) { // Indeed
                            bmpFile.read(sdbuffer, sizeof(sdbuffer));
                            buffidx = 0; // Set index to beginning
                        }

                        // Convert pixel from BMP to TFT format, push to display
                        b = sdbuffer[buffidx++];
                        g = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];
                        tft.pushColor(tft.Color565(r,g,b));
                    } // end pixel
                } // end scanline
                Serial.print("Loaded in ");
                Serial.print(millis() - startTime);
                Serial.println(" ms");
            } // end goodBmp
        }
    }

    bmpFile.close();
    if(!goodBmp) Serial.println("BMP format not recognized.");
}

void testdrawtext(char *text, uint16_t color) {
    tft.setCursor(0, 0);
    tft.setTextColor(color);
    tft.setTextWrap(true);
    tft.print(text);
}

void testlines(uint16_t color) {
    tft.fillScreen(ST7735_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6) {
        tft.drawLine(0, 0, x, tft.height()-1, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6) {
        tft.drawLine(0, 0, tft.width()-1, y, color);
    }

    tft.fillScreen(ST7735_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6) {
        tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6) {
        tft.drawLine(tft.width()-1, 0, 0, y, color);
    }

    tft.fillScreen(ST7735_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6) {
        tft.drawLine(0, tft.height()-1, x, 0, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6) {
        tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    }

    tft.fillScreen(ST7735_BLACK);
    for (int16_t x=0; x < tft.width(); x+=6) {
        tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    }
    for (int16_t y=0; y < tft.height(); y+=6) {
        tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    }
}

void setup(void) {
    Serial.begin(9600);
    Serial.print("Hello! professorbunsen, I presume? ");

    // Use this initializer if you're using a 1.8" TFT
    //tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

    // Use this initializer (uncomment) if you're using a 1.44" TFT
    tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
        Serial.println("failed!");
        return;
    }
    Serial.println("OK!");

    Serial.println("Initialized");

    uint16_t time = millis();
    tft.fillScreen(ST7735_BLACK);
    time = millis() - time;

    Serial.println(time, DEC);
    delay(2000);

}

void loop(void) {

    // change the name here!
    bmpDraw("robot.bmp", 0, 0);
    delay(2000);


}


