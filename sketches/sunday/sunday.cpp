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
T_bmp[] =
{ B11111111,
B11111111,
B00011000,
B00011000,
B00011000,
B00011000,
B00011000,
B00011000 },
H_bmp[] =
{ B11000011,
B11000011,
B11000011,
B11111111,
B11111111,
B11000011,
B11000011,
B11000011 },
L_bmp[] =
{ B11100000,
B11100000,
B11100000,
B11100000,
B11100000,
B11111111,
B11111111,
B11111111 },
I_bmp[] =
{ B00111000,
B00111000,
B00111000,
B00111000,
B00111000,
B00111000,
B00111000,
B00111000 },
S_bmp[] =
{ B11111111,
B11111111,
B11000000,
B11111111,
B11111111,
B00000011,
B11111111,
B11111111 },
B_bmp[] =
{ B11111110,
B11100011,
B11100011,
B11111110,
B11110001,
B11110001,
B11111111,
B11111110 },
E_bmp [] =
{ B11111111,
B11111111,
B11100000,
B11111110,
B11111110,
B11100000,
B11111111,
B11111111 },
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
    matrix.drawBitmap(0, 0, L_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    matrix.clear();
    matrix.drawBitmap(0, 0, I_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    matrix.clear();
    matrix.drawBitmap(0, 0, S_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    matrix.clear();
    matrix.drawBitmap(0, 0, B_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    matrix.clear();
    matrix.drawBitmap(0, 0, E_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    matrix.clear();
    matrix.drawBitmap(0, 0, T_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);

    matrix.clear();
    matrix.drawBitmap(0, 0, H_bmp, 8, 8, LED_ON);
    matrix.writeDisplay();
    delay(1000);
}
