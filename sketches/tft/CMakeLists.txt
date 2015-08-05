# add a target and tell it what it's source files are
add_executable_avr(tft tft.cpp)
# tell the target, that it should use the arduino core libraries
target_link_libraries(tft arduino-core)
target_sketch_library(tft Adafruit-GFX-Library https://github.com/adafruit/Adafruit-GFX-Library)
target_sketch_library(tft Adafruit-ST7735-Library https://github.com/adafruit/Adafruit-ST7735-Library)
