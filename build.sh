#!/bin/bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=../cmake/gcc-arm-none-eabi.cmake
cmake --build build
cd build
arm-none-eabi-objcopy -O binary lcd1602a_display_driver.elf lcd1602a_display_driver.bin
arm-none-eabi-objcopy -O ihex   lcd1602a_display_driver.elf lcd1602a_display_driver.hex
cd ..
