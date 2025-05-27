#!/bin/bash

# Compiler le code Arduino avec avrdude
arduino-cli compile --fqbn arduino:avr:uno src/pedro_main.ino

# Utiliser avrdude pour flasher le fichier .hex
avrdude -v -p m328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:build/pedro_main.hex:i
