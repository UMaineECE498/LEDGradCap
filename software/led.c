// A. Sheaff 1/24/2015
// ECE 498 Blinky LED stuff
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "led.h"

// Sends one bit to LEDS
// 'r' is the register variable that contains the bit to send
// sends bit at bit position 'b'
// p is the port for the output TX
// n is the pin on port p
// Automagically sends the correct timing based on the bit value
#define TX_BIT(r,b,p,n) do { asm volatile ( \
	"sbi %2,%3\n\t" \
	"sbrs %0,%1\n\t" \
	"cbi %2,%3\n\t" \
	"nop\t\n" \
	"sbrc %0,%1 \n\t" \
	"cbi %2,%3\n\t" \
	"nop\n\t" \
	: \
	: "d" (r), "M" (b), "I"  (_SFR_IO_ADDR(p)), "M" (n) \
	: \
	); } while (0)

// Sends a serial bit stream to string of LEDS
// ra contains ! 8 ! red values
// rb contains ! 8 ! green values
// rc contains ! 8 ! blue values
void send_leds(uint8_t *ra, uint8_t *ga, uint8_t *ba)
{
	register uint8_t c;	// this MUST be a register
	register uint8_t i=0;	// this MUST be a register

	cli();	// Not interrupts in the critial timing area
	for (i=0;i<8;i++) {	// For each led
		c=ga[i];		// Red
		TX_BIT(c,7,PORTB,3);	// Each bit
		TX_BIT(c,6,PORTB,3);
		TX_BIT(c,5,PORTB,3);
		TX_BIT(c,4,PORTB,3);
		TX_BIT(c,3,PORTB,3);
		TX_BIT(c,2,PORTB,3);
		TX_BIT(c,1,PORTB,3);
		TX_BIT(c,0,PORTB,3);
		c=ra[i];		// Green
		TX_BIT(c,7,PORTB,3);	// Each bit
		TX_BIT(c,6,PORTB,3);
		TX_BIT(c,5,PORTB,3);
		TX_BIT(c,4,PORTB,3);
		TX_BIT(c,3,PORTB,3);
		TX_BIT(c,2,PORTB,3);
		TX_BIT(c,1,PORTB,3);
		TX_BIT(c,0,PORTB,3);
		c=ba[i];		// Blue
		TX_BIT(c,7,PORTB,3);	// Each bit
		TX_BIT(c,6,PORTB,3);
		TX_BIT(c,5,PORTB,3);
		TX_BIT(c,4,PORTB,3);
		TX_BIT(c,3,PORTB,3);
		TX_BIT(c,2,PORTB,3);
		TX_BIT(c,1,PORTB,3);
		TX_BIT(c,0,PORTB,3);
	}
	sei();
	return;
}
