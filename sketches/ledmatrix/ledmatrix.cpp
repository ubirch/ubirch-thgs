/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x8matrix matrix_70 = Adafruit_8x8matrix();
//Adafruit_8x8matrix matrix_71 = Adafruit_8x8matrix();

void demo();

void setup() {
    Serial.begin(9600);
    Serial.println("8x8 LED Matrix Test");

    // 0x70 + 00 = 0x70 DEFAULT
    // 0x70 + 01 = 0x71 A0 connected
    // 0x70 + 10 = 0x72 A1 connect
    // 0x70 + 11 = 0x73 A0 & A1 connected
    matrix_70.begin(0x70);  // pass in the address
//    matrix_71.begin(0x01);
}

static const uint8_t PROGMEM
        smile_bmp[] =
        {B00111100,
         B01000010,
         B10100101,
         B10000001,
         B10100101,
         B10011001,
         B01000010,
         B00111100},
        neutral_bmp[] =
        {B00111100,
         B01000010,
         B10100101,
         B10000001,
         B10111101,
         B10000001,
         B01000010,
         B00111100},
        frown_bmp[] =
        {B00111100,
         B01000010,
         B10100101,
         B10000001,
         B10011001,
         B10100101,
         B01000010,
         B00111100};

static const uint8_t PROGMEM
        pb_pattern[] =
        {B00000000,
         B00000000,
         B00111100,
         B00000100,
         B00000100,
         B00000100,
         B00000000,
         B00000000};

void loop() {
//    demo();

    matrix_70.clear();
    matrix_70.drawBitmap(0, 0, pb_pattern, 8, 8, LED_ON);
    matrix_70.writeDisplay();
    delay(500);

    int x = rand() % 7;
    int y = rand() % 7;
    matrix_70.drawPixel(x, y, LED_ON);
    matrix_70.writeDisplay();  // write the changes we just made to the display
    delay(150);
}

void demo() {
    matrix_70.clear();
    matrix_70.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
    matrix_70.writeDisplay();
    delay(500);

    matrix_70.clear();
    matrix_70.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_ON);
    matrix_70.writeDisplay();
    delay(500);

    matrix_70.clear();
    matrix_70.drawBitmap(0, 0, frown_bmp, 8, 8, LED_ON);
    matrix_70.writeDisplay();
    delay(500);

    matrix_70.clear();      // clear display
    matrix_70.drawPixel(0, 0, LED_ON);
    matrix_70.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix_70.clear();
    matrix_70.drawLine(0, 0, 7, 7, LED_ON);
    matrix_70.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix_70.clear();
    matrix_70.drawRect(0, 0, 8, 8, LED_ON);
    matrix_70.fillRect(2, 2, 4, 4, LED_ON);
    matrix_70.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix_70.clear();
    matrix_70.drawCircle(3, 3, 3, LED_ON);
    matrix_70.writeDisplay();  // write the changes we just made to the display
    delay(500);

    matrix_70.setTextSize(1);
    matrix_70.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
    matrix_70.setTextColor(LED_ON);
    for (int8_t x = 0; x >= -36; x--) {
        matrix_70.clear();
        matrix_70.setCursor(x, 0);
        matrix_70.print("ubirch");
        matrix_70.writeDisplay();
        delay(100);
    }
    matrix_70.setRotation(3);
    for (int8_t x = 7; x >= -36; x--) {
        matrix_70.clear();
        matrix_70.setCursor(x, 0);
        matrix_70.print("#1");
        matrix_70.writeDisplay();
        delay(100);
    }
    matrix_70.setRotation(0);
}
