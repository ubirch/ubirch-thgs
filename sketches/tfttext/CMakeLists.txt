# add a target and tell it what it's source files are
add_executable_avr(tfttext tfttext.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(tfttext arduino-core)
target_sketch_library(tfttext Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(tfttext Adafruit-ST7735-Library https://github.com/adafruit/Adafruit-ST7735-Library)
