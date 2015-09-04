# add a target and tell it what it's source files are
add_executable_avr(tftbitmap tftbitmap.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(tftbitmap arduino-core)
target_sketch_library(tftbitmap Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(tftbitmap Adafruit-ST7735-Library https://github.com/adafruit/Adafruit-ST7735-Library)
target_sketch_library(tftbitmap SD https://github.com/adafruit/SD)
target_sketch_library(tftbitmap Adafruit-LED-Backback-Library https://github.com/adafruit/Adafruit-LED-Backpack-Library)