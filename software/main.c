// A. Sheaff 1/24/2015
// ECE 498 Blinky LED stuff
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <stdio.h>

#include "i2cmaster.h"

#define BAUD 9600

#include <util/setbaud.h>


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

#define MMA7660_ADR 0x4C


// TODO: Remove these help functions later
void uart_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}


void serial_print(char * c)
{
	while(*c)
	{
		while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
		UDR0 = *(c++); // Echo back the received byte back to the computer
	}
}

int main(void)
{
	unsigned char ret = 5;
	unsigned char x_axis = 0;
	char serial[30] = {0};
	char * serial_pointer;

	uart_init();
	i2c_init();

	// heartbeat led
	DDRD |= 1 << 2;

	// Initialize accel
	i2c_start_wait((MMA7660_ADR << 1) + I2C_WRITE);
	i2c_write(0x07); 		// Set Device in active Mode
	i2c_write(0x01);		// Write active mode bit
	i2c_stop();

	while(1)
	{
		// I2C Sample Loop
		ret = i2c_start((MMA7660_ADR << 1) + I2C_WRITE);

		ret = i2c_write(0x00); 		// Set to read from x axis register
		i2c_rep_start((MMA7660_ADR << 1) + I2C_READ);
		x_axis = i2c_readNak();		// Read Value

		// Bit 6 signifies error per datasheet
		if (x_axis & (1<<6))
		{
			sprintf(serial, "X Axis: Alert\n");
		} else {
			sprintf(serial, "X Axis: %X\r\n", x_axis);
		}

		// Output to serail
		serial_print(serial);

		// I2C transfer done
		i2c_stop();

		// Heartbeat LED
		PORTD ^= (1 << 2);
		_delay_ms(100);
	}





	// // Colors to send
	// uint8_t g[8], r[8], b[8];
	// uint8_t i=0, rx=0, gx=0, bx=0, idx=0;

	// // Setup output and extra timing pin to trigger scope
	// DDRB|=_BV(PIN3);	// LED TX
	// DDRC|=_BV(PIN0);	// LED TX
	// // Fetch pattern data
	// for (i=0;i<8;i++) {
	// 	r[i]=eeprom_read_byte(&rgb[i]);
	// 	g[i]=eeprom_read_byte(&rgb[i+8]);
	// 	b[i]=eeprom_read_byte(&rgb[i+8+8]);
	// }
	// while (1) {
	// 	PORTC|=_BV(PIN0);
	// 	send_leds(r,g,b);	// Send
	// 	PORTC&=~_BV(PIN0);
	// 	if (idx<5) {
	// 		rx=r[0];
	// 		gx=g[0];
	// 		bx=b[0];
	// 		for (i=0;i<7;i++) {
	// 			r[i]=r[i+1];
	// 			g[i]=g[i+1];
	// 			b[i]=b[i+1];
	// 		}
	// 		r[7]=rx;
	// 		g[7]=gx;
	// 		b[7]=bx;
	// 	} else {
	// 		rx=r[7];
	// 		gx=g[7];
	// 		bx=b[7];
	// 		for (i=0;i<7;i++) {
	// 			r[7-i]=r[7-i-1];
	// 			g[7-i]=g[7-i-1];
	// 			b[7-i]=b[7-i-1];
	// 		}
	// 		r[0]=rx;
	// 		g[0]=gx;
	// 		b[0]=bx;
	// 	}
	// 	idx++;
	// 	if (idx>=10) idx=0;
	// 	_delay_ms(100);
	// 	// The LEDs all hold their value so we can
	// 	// go off and caclulate new values or sleep, whatever
	// }			
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