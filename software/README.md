Software
==========
This directory contains the software which will be used on the blinky board.

## Setting the atmega1284p to 8MhZ
    avrdude -p atmega1284p -P usb -c avrispmkII -U lfuse:w:0xc2:m -U hfuse:w:0x99:m -U efuse:w:0xff:m
