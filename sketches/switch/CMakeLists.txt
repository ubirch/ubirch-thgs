# add a target and tell it what it's source files are
add_executable_avr(switch switch.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(switch arduino-core)
target_sketch_library(switch Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(switch Adafruit-ST7735-Library https://github.com/adafruit/Adafruit-ST7735-Library)
target_sketch_library(switch SD https://github.com/adafruit/SD)
target_sketch_library(switch Adafruit-LED-Backback-Library https://github.com/adafruit/Adafruit-LED-Backpack-Library)