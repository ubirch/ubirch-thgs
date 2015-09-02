# add a target and tell it what it's source files are
add_executable_avr(thgsmodul thgsmodul.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(thgsmodul arduino-core)
target_sketch_library(thgsmodul Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(thgsmodul Adafruit-ST7735-Library https://github.com/adafruit/Adafruit-ST7735-Library)
target_sketch_library(thgsmodul SD https://github.com/adafruit/SD)
target_sketch_library(thgsmodul Adafruit-LED-Backback-Library https://github.com/adafruit/Adafruit-LED-Backpack-Library)