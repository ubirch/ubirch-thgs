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

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
    Serial.begin(9600);
    Serial.println("8x8 LED Matrix Test");

    matrix.begin(0x70);  // pass in the address
}


//Symbols for LoF
static const uint8_t PROGMEM
        zero_bmp[] =
        { B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00100000,
          B00000000,
          B00000000 },
        one_bmp[] =
        { B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B11100000,
          B00100000,
          B00100000 },
        two_bmp[] =
        { B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B11111100,
          B00100100,
          B00100100 },
        three_bmp[] =
        { B00000000,
          B00000000,
          B00000000,
          B11111000,
          B00001000,
          B11101000,
          B00101000,
          B00101000 },
        four_bmp[] =
        { B00000000,
          B00000000,
          B00000000,
          B11111000,
          B11111000,
          B11111000,
          B00111000,
          B00111000 },
        five_bmp[] =
        { B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B11100000,
          B11100000,
          B11100000 },
        six_bmp [] =
        { B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B11111100,
          B11100100,
          B11100100 },
        seven_bmp [] =
        { B00000000,
          B00000000,
          B00000000,
          B11111111,
          B00000001,
          B11111101,
          B11100101,
          B11100101 },
        eight_bmp [] =
        { B00000000,
          B00000000,
          B00000000,
          B11111111,
          B11111111,
          B11111111,
          B11100111,
          B11100111 },
        nine_bmp [] =
        { B00000000,
          B00000000,
          B00000000,
          B00000000,
          B00000000,
          B11111100,
          B11111100,
          B11111100 },
        ten_bmp [] =
        { B00000000,
          B00000000,
          B11111100,
          B11111100,
          B00001100,
          B11101100,
          B11101100,
          B11101100 },
        eleven_bmp [] =
        { B11111111,
          B00000001,
          B11111101,
          B11111101,
          B00001101,
          B11101101,
          B11101101,
          B11101101 },
        twelve_bmp [] =
        { B11111111,
          B11111111,
          B11111111,
          B11111111,
          B11111111,
          B11111111,
          B11111111,
          B11111111 };






void loop() {

    matrix.clear();
    matrix.drawBitmap(0, 0, zero_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, one_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, two_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, three_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, four_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(500);

    matrix.clear();
    matrix.drawBitmap(0, 0, five_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, six_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, seven_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, eight_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(500);

    matrix.clear();
    matrix.drawBitmap(0, 0, nine_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, five_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, ten_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, eleven_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);

    matrix.clear();
    matrix.drawBitmap(0, 0, twelve_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(5000);
}
