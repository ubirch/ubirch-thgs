# add a target and tell it what it's source files are
add_executable_avr(prototype prototype.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(prototype arduino-core)
target_sketch_library(prototype Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(prototype Adafruit-ST7735-Library https://github.com/adafruit/Adafruit-ST7735-Library)
target_sketch_library(prototype SD https://github.com/adafruit/SD)
target_sketch_library(prototype Adafruit-LED-Backback-Library https://github.com/adafruit/Adafruit-LED-Backpack-Library)