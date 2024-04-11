cmake_minimum_required(VERSION 3.27)
# Get the toolchain automatically.
include(${CMAKE_SOURCE_DIR}/cmake-avr/generic-gcc-avr.cmake)

set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER atmega328p)
set(AVR_UPLOADTOOL_PORT usb)

# AVR and fuses needs to be set
set(AVR_MCU atmega328p)
set(AVR_H_FUSE 0xd9)
set(AVR_L_FUSE 0xc3)

# Run at 20 Mhz.
set(MCU_SPEED "15400000UL")

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

if(DEFINED ENV{AVR_FIND_ROOT_PATH})
    set(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
else(DEFINED ENV{AVR_FIND_ROOT_PATH})
    if(EXISTS "/opt/local/avr")
      set(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
    elseif(EXISTS "/usr/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/avr")
    elseif(EXISTS "/usr/lib/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
    elseif(EXISTS "/usr/local/CrossPack-AVR")
      set(CMAKE_FIND_ROOT_PATH "/usr/local/CrossPack-AVR")
    else(EXISTS "/opt/local/avr")
      message(FATAL_ERROR "Please set AVR_FIND_ROOT_PATH in your environment.")
    endif(EXISTS "/opt/local/avr")
endif(DEFINED ENV{AVR_FIND_ROOT_PATH})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# not added automatically, since CMAKE_SYSTEM_NAME is "generic"
set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")
message(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
message(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
message(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")

set(CMAKE_CXX_EXTENSIONS ON)
set(CXX_STANDARD 23)
project(bin CXX C ASM)
file(GLOB arduino_srcs
  ${CMAKE_CURRENT_SOURCE_DIR}/ArduinoCore-avr/cores/arduino/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ArduinoCore-avr/cores/arduino/*.c
)

add_avr_executable(bin
  main.cpp
  ${arduino_srcs}
  ${CMAKE_CURRENT_SOURCE_DIR}/Adafruit_NeoPixel/Adafruit_NeoPixel.cpp
)

# `target_add_definitions` and `target_compile_options` do not work with this toolchain.
add_definitions(
  "-DARDUINO=100"
  "-DF_CPU=${MCU_SPEED}"
  "-fpack-struct"
  "-fshort-enums"
  "-Wall" "-Wextra" "-Wdangling-pointer" "-Wconversion"
  "-fmerge-all-constants"
  "-funsigned-char"
  "-funsigned-bitfields"
  "-ffunction-sections"
  "-c"
  # It is required that we build with optimizations.
  "-Os"
)

# Add headers.
avr_target_include_directories(bin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ArduinoCore-avr/cores/arduino/)
avr_target_include_directories(bin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ArduinoCore-avr/variants/standard/)
avr_target_include_directories(bin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Adafruit_NeoPixel/)
