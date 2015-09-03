# add a target and tell it what it's source files are
add_executable_avr(ledLOFlogic ledLOFlogic.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(ledLOFlogic arduino-core)
target_sketch_library(ledLOFlogic Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(ledLOFlogic Adafruit-LED-Backback-Library https://github.com/adafruit/Adafruit-LED-Backpack-Library)