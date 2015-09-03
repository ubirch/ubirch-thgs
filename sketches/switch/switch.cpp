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

#define DEBOUNCE_TIME 1000
#define PIN_LED 13
#define PIN_BUTTON A0

//Symbols for LoF
static const uint8_t PROGMEM

        logothgs_bmp[] =
        {B00000000,
         B00100100,
         B00100100,
         B01111110,
         B00100100,
         B00100100,
         B00000000,
         B00000000},
        logoLOF_bmp[] =
        {B00000000,
         B00000000,
         B00111100,
         B00000100,
         B00000100,
         B00000100,
         B00000000,
         B00000000},
        OSN_bmp[] =
        {B01100111,
         B10010100,
         B10010111,
         B10010001,
         B01100111,
         B00000000,
         B01111110,
         B00000000},
        x_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B00000000,
         B00000000,
         B00000000,
         B00000000,
         B10000000},
        y_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B00000000,
         B00000000,
         B11100000,
         B00100000,
         B10100000},
        z_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B00000000,
         B00000000,
         B00000000,
         B11000000,
         B11000000},
        y2_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B00000000,
         B11110000,
         B00010000,
         B11010000,
         B11010000},
        x3_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B00000000,
         B00000000,
         B11100000,
         B11100000,
         B11100000},
        y3_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B11111000,
         B00001000,
         B11101000,
         B11101000,
         B11101000},
        x4_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B00000000,
         B11110000,
         B11110000,
         B11110000,
         B11110000},
        y4_bmp[] =
        {B00000000,
         B00000000,
         B11111100,
         B00000100,
         B11110100,
         B11110100,
         B11110100,
         B11110100},
        x5_bmp[] =
        {B00000000,
         B00000000,
         B00000000,
         B11111000,
         B11111000,
         B11111000,
         B11111000,
         B11111000},
        y5_bmp[] =
        {B00000000,
         B11111110,
         B00000010,
         B11111010,
         B11111010,
         B11111010,
         B11111010,
         B11111010},
        x6_bmp[] =
        {B00000000,
         B00000000,
         B11111100,
         B11111100,
         B11111100,
         B11111100,
         B11111100,
         B11111100},
        y6_bmp[] =
        {B11111111,
         B00000001,
         B11111101,
         B11111101,
         B11111101,
         B11111101,
         B11111101,
         B11111101},
        x7_bmp[] =
        {B00000000,
         B11111110,
         B11111110,
         B11111110,
         B11111110,
         B11111110,
         B11111110,
         B11111110},
        z2_bmp[] =
        {B11111111,
         B11111111,
         B11111111,
         B11111111,
         B11111111,
         B11111111,
         B11111111,
         B11111111},
        logothgsinvers_bmp[] =
        {B11111111,
         B11011011,
         B11011011,
         B10000001,
         B11011011,
         B11011011,
         B11111111,
         B11111111},
        logoLOFinvers_bmp[] =
        {B11111111,
         B11111111,
         B11000011,
         B11111011,
         B11111011,
         B11111011,
         B11111111,
         B11111111};


void setup() {
    Serial.begin(BAUD);
    Serial.println("8x8 LED Matrix Test");
    matrix.begin(0x70);  // pass in the address

    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);

    // initialize with the first image
    matrix.clear();
    matrix.drawBitmap(0, 0, logoLOF_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
}

int debounce = 0;
int bmpState = 0;

void loop() {

    int switchState = 0;
    switchState = digitalRead(PIN_BUTTON);
    //pin3

    if (switchState == LOW) debounce++; else debounce = 0;

    // if the switch is in state high it is pressed, do something
    if (debounce > DEBOUNCE_TIME) {
        digitalWrite(PIN_LED, HIGH);

        matrix.clear();
        // ++bmpState increases the bmp
        switch (++bmpState) {
            case 1:
                matrix.drawBitmap(0, 0, OSN_bmp, 8, 8, LED_ON);
                break;
            case 2:
                matrix.drawBitmap(0, 0, x_bmp, 8, 8, LED_ON);
                break;
            case 3:
                matrix.drawBitmap(0, 0, y_bmp, 8, 8, LED_ON);
                break;
            default:
                bmpState = 0;
                matrix.drawBitmap(0, 0, logoLOF_bmp, 8, 8, LED_ON);
        }
        matrix.writeDisplay();

    } else {
        digitalWrite(PIN_LED, HIGH);
    }

}