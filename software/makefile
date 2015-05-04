TARGET=gradcap
CPU=attiny20
F_CPU=8000000UL

CC=/usr/local/atmel/bin/avr-gcc
CFLAGS=-funsigned-char -funsigned-bitfields -ffunction-sections -fno-inline-small-functions -fpack-struct -fshort-enums -fno-strict-aliasing -fno-split-wide-types -Wall -Wstrict-prototypes -std=gnu99 -MMD -MP -O2 -mmcu=${CPU}
CFLAGS += -DF_CPU=$(F_CPU)
SIZE=/usr/local/atmel/bin/avr-size
LIBS=
AVRDUDE=avrdude
ifeq ($(USER),sheaff)
AVRDUDE=/usr/local/bin/avrdude
endif
AVDFLAGS=-p t20 -P usb -c avrispmkII -F
OBJCOPY=/usr/local/atmel/bin/avr-objcopy
OBJCFLAGS=-O ihex -R .eeprom -R .fuse -R .lock

OBJS=main.o led.o i2cmaster.S accel.o ledRoutines.o
#LDFLAGS=-Wl,-u,vfprintf -lprintf_min

.PHONY: program clean

program: ${TARGET}.hex
	${AVRDUDE} ${AVDFLAGS} -U flash:w:${TARGET}.hex

${TARGET}.hex: ${TARGET}
	${OBJCOPY} ${OBJCFLAGS} ${TARGET} ${TARGET}.hex
	${SIZE} ${TARGET}

${TARGET}: ${OBJS}
	${CC} -mmcu=${CPU} -o ${TARGET} ${LDFLAGS} ${OBJS}

clean:
	rm -f ${TARGET} *.o *.d
