#!/bin/bash
pyocd erase --target py32f003x8 -s 0x08000000+0x10000
pyocd flash --target py32f003x8 -a 0x08000000 build/main.hex
pyocd reset --target py32f003x8