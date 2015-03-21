// A. Sheaff 1/24/2015
// ECE 498 Blinky LED stuff
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

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

// Send 8, 24 bit "frames" to 8 leds.
void send_leds(uint8_t *ra, uint8_t *ga, uint8_t *ba);

// Pattern data
const uint8_t EEMEM rgb[] = {
	0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x0F,	// Red
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	// Green
	0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,	// Blue
};

int main(void)
{
	// Colors to send
	uint8_t g[8], r[8], b[8];
	uint8_t i=0, rx=0, gx=0, bx=0, idx=0;

	// Setup output and extra timing pin to trigger scope
	DDRB|=_BV(PIN3);	// LED TX
	DDRC|=_BV(PIN0);	// LED TX
	// Fetch pattern data
	for (i=0;i<8;i++) {
		r[i]=eeprom_read_byte(&rgb[i]);
		g[i]=eeprom_read_byte(&rgb[i+8]);
		b[i]=eeprom_read_byte(&rgb[i+8+8]);
	}
	while (1) {
		PORTC|=_BV(PIN0);
		send_leds(r,g,b);	// Send
		PORTC&=~_BV(PIN0);
		if (idx<5) {
			rx=r[0];
			gx=g[0];
			bx=b[0];
			for (i=0;i<7;i++) {
				r[i]=r[i+1];
				g[i]=g[i+1];
				b[i]=b[i+1];
			}
			r[7]=rx;
			g[7]=gx;
			b[7]=bx;
		} else {
			rx=r[7];
			gx=g[7];
			bx=b[7];
			for (i=0;i<7;i++) {
				r[7-i]=r[7-i-1];
				g[7-i]=g[7-i-1];
				b[7-i]=b[7-i-1];
			}
			r[0]=rx;
			g[0]=gx;
			b[0]=bx;
		}
		idx++;
		if (idx>=10) idx=0;
		_delay_ms(100);
		// The LEDs all hold their value so we can
		// go off and caclulate new values or sleep, whatever
	}			
}

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