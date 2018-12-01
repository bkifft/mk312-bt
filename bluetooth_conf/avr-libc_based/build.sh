#!/bin/bash

#makefile would be overkill
rm mk312-bt_hc-05_tool.bin mk312-bt_hc-05_tool.hex mk312-bt_hc-05_tool.elf mk312-bt_hc-05_tool.lst
avr-gcc -O1 -g -mmcu=atmega16 -DF_CPU=8000000 -D_LCD_DEFINITIONS_FILE -Wall -Werror -o mk312-bt_hc-05_tool.elf mk312-bt_hc-05_tool.c uart.c lcd.c
avr-objdump -h -S mk312-bt_hc-05_tool.elf > mk312-bt_hc-05_tool.lst
avr-objcopy -j .text -j .data -O ihex mk312-bt_hc-05_tool.elf mk312-bt_hc-05_tool.hex
avr-objcopy -j .text -j .data -O binary mk312-bt_hc-05_tool.elf mk312-bt_hc-05_tool.bin

avrdude -c usbasp -p m16 -U "flash:w:mk312-bt_hc-05_tool.bin"

