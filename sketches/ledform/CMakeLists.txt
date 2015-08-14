# add a target and tell it what it's source files are
add_executable_avr(ledform ledform.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(ledform arduino-core)
target_sketch_library(ledform Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(ledform Adafruit-LED-Backback-Library https://github.com/adafruit/Adafruit-LED-Backpack-Library)