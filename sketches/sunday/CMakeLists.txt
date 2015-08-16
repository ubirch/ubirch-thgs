# add a target and tell it what it's source files are
add_executable_avr(sunday sunday.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(sunday arduino-core)
target_sketch_library(sunday Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(sunday Adafruit-LED-Backback-Library https://github.com/adafruit/Adafruit-LED-Backpack-Library)