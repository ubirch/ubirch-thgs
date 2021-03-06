#=====================================================================================
# ubirch #1 cmake configuration
#=====================================================================================
cmake_minimum_required(VERSION 3.0)

# the toolchain file (see https://github.com/ubirch/avr-arduino-cmake)
set(CMAKE_TOOLCHAIN_FILE cmake/avr-arduino-toolchain.cmake)

# if you want to compile Arduino sketches, set this to the Arduino SDK dir (1.6.5)
set(ARDUINO_SDK_PATH "/Applications/Arduino.app/Contents/Java" CACHE STRING "Arduino SDK Path")

# project name and code types we use
project(ubirch C CXX ASM)

# necessary settings for the chip we use
set(MCU atmega328p)
set(F_CPU 16000000)
set(BAUD 115200)

# set the programmer and the device to use (default is to use simavr)
set(PROGRAMMER arduino)
set(SERIAL_DEV /dev/cu.usbmodem1421)

# only needed if we do floating point math and want to print floats with printf
#set(EXTRA_LIBS "-lm -lprintf_flt")

# add the sketches directory (contains sketch directories and a "libraries" dir where dependent
# libs are extracted
add_sketches(sketches)