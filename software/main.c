
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "system.h"
#include "i2cmaster.h"
#include "led.h"
#include "accel.h"

int grad_cap_mode(void);
void do_grad_cap(void);
void do_shaky_shaky(void);
uint8_t tilted_to_left(void);
// Initialize the system
void system_init(void);
void display_msg(void);

// Pattern routines
//void fade(uint8_t *red, uint8_t *green, uint8_t *blue, uint8_t inOrOut);
void simpleFade(uint8_t *colorToFade, uint8_t inOrOut);


#define NUM_LOOPS 10		//number of loops
#define MAX_STEPS 5		//

#define IN 1        //  Fade directions
#define OUT -1

uint8_t red[8] = { 0 };	// Red values
uint8_t green[8] = { 0 };	// Green values
uint8_t blue[8] = { 0 };	// Blue values

int main(void)
{
	int8_t x[8];		// X axis accel values
	uint8_t i = 0;		// X axis index
	uint8_t j = 0;		// General index
	int16_t a = 0;		// Average value

	system_init();		// System init
	send_leds(red, green, blue);	// Write

    //  Fade test
    //  Set colors up, then fade in & out
    simpleFade(red, IN);
    _delay_ms(750);
    simpleFade(red, OUT);
    _delay_ms(750);

    simpleFade(green, IN);
    _delay_ms(750);
    simpleFade(green, OUT);
    _delay_ms(750);

    simpleFade(blue, IN);
    _delay_ms(750);
    simpleFade(blue, OUT);
    _delay_ms(750);

	while (1) {
		x[i] = accel_reg_read(ACCEL_X_AXIS) & 0x3F;	// Get X axis
		if (x[i] & 0x20) {
			x[i] = x[i] | 0xc0;
		}
		i++;
		i = i & 0x07;
		a = 0;
		for (j = 0; j < 8; j++) {	// Average
			a += x[j];
		}
		a = a / 8;
		if (a>20) {
			grad_cap_mode();
		}
	}
	return 0;
}


/*
 *  This assumes colors are all at 0;
 */
void simpleFade(uint8_t *colorToFade, uint8_t inOrOut)
{
    uint8_t i,j;

    if (inOrOut == IN)
    {
        for (i=0; i<8; i++)
        {
            *(colorToFade+i) = 0;
        }
    }
    else
    {
        for (i=0; i<8; i++)
        {
            *(colorToFade+i) = 64;
        }
    }

    //  Max value for any color is 64
    for (j=0; j<64; j++)
    {
		send_leds(red, green, blue);

        for (i=0; i<8; i++)
        {
            *(colorToFade+i) += inOrOut;
        }

		_delay_ms(50);
    }
}
#if 0
/*
 *  This version's too big.
 */
void fade(uint8_t *red, uint8_t *green, uint8_t *blue, uint8_t inOrOut)
{
	uint8_t i, j;
    uint8_t tr[8] = { 0 };	// Red values
    uint8_t tg[8] = { 0 };	// Green values
    uint8_t tb[8] = { 0 };	// Blue values


    if (inOrOut == IN)
    {
        for (i=0; i<8; i++)
        {
            *(tr+i) = *(red+i);
            *(tg+i) = *(green+i);
            *(tb+i) = *(blue+i);
        }
    }
    else
    {
        for (i=0; i<8; i++)
        {
            *(tr+i) = 0;
            *(tg+i) = 0;
            *(tb+i) = 0;
        }
    }

    //  Max value for any color is 128
    for (j=0; j<128; j++)
    {
		send_leds(tr, tg, tb);

        for (i=0; i<8; i++)
        {
            if (inOrOut == IN)
            {
                if ( *(tr+i) < *(red+i) )
                {
                    *(tr+i) += 1;
                }
                if ( *(tg+i) < *(green+i) )
                {
                    *(tg+i) += 1;
                }
                if ( *(tb+i) < *(blue+i) )
                {
                    *(tb+i) += 1;
                }
            }
            else
            {
                if ( *(tr+i) > 0 )
                {
                    *(tr+i) -= 1;
                }
                if ( *(tg+i) > 0 )
                {
                    *(tg+i) -= 1;
                }
                if ( *(tb+i) > 0 )
                {
                    *(tb+i) -= 1;
                }
            }
        }

		_delay_ms(50);
    }
}
#endif

// if Z~=1G I'm Flat
// if Z~=0 I'm Shaky Shaky
int grad_cap_mode(void)
{
	uint8_t z = 0;

	while (1) {
		z = accel_reg_read(ACCEL_Z_AXIS) & 0x3F;
		if (z > 16) {
			return 1;
		}

	}

	return 0;
}

void do_grad_cap(void)
{
	int step = 0;
	int loops = 0;

	while (grad_cap_mode()) {
		if (loops < NUM_LOOPS) {
			//change_leds(step);
		}
		step++;
		if (step > MAX_STEPS) {
			step = 0;
			loops++;
		}

		if (accel_reg_read(ACCEL_X_AXIS) & 0x3F) {
			step = 0;
			loops = 0;
		}
		//@todo determine the best delay, sleep?
		_delay_ms(100);
	}
}
#if 0
//detect a clap show a flash of Maine Blue

enum { RIGHT, CCW, LEFT, CWDISP, CWBLANK };

// This does not work
void do_shaky_shaky(void)
{
	uint8_t state = CCW;
	int8_t x;

	while (1) {
		x = accel_reg_read(ACCEL_X_AXIS) & 0x3F;	// Get X axis
		if (x > 31)
			x = x - 64;
		switch (state) {
			case CWDISP:	// Starting CW travel - display message once
				display_msg();
				state = CWBLANK;
				break;
			case CWBLANK:	// Message ended but still traveling CW
				if (x == 31)
					state = RIGHT;	// Wait until at right
				break;
			case CCW:	// Traveling CCW - no message
				if (x == -32)
					state = LEFT;	// Wait until at left
				break;
			case RIGHT:	// At right extreme
				if (x < 31)
					state = CCW;	// Wait until turn around
				break;
			case LEFT:	// At left extreme
				if (x > -32)
					state = CWDISP;	// Wait until turn around
				break;
		}
	}
	return;
}

const uint8_t msg[] PROGMEM={
				0x00,0x00,0x7f,
				0x00,0x00,0x02,
				0x00,0x00,0x04,
				0x00,0x00,0x02,
				0x00,0x00,0x7f,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x41,
				0x00,0x00,0x41,
				0x00,0x00,0x7f,
				0x00,0x00,0x41,
				0x00,0x00,0x41,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x7f,
				0x00,0x00,0x08,
				0x00,0x00,0x14,
				0x00,0x00,0x22,
				0x00,0x00,0x41,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x7f,
				0x00,0x00,0x49,
				0x00,0x00,0x49,
				0x00,0x00,0x49,
				0x00,0x00,0x41,
};
#define MSGLEN 87

void display_msg(void)
{
	unsigned char i;

	// String index
	i = 0;
	while (m[i]) {		// For each character
		_delay_us(2000);
		i++;		// Next letter
		if (i >= strlen(m))
			return;	// Bail if end of string
		if (i >= limit)
			return;	// Bail if limit reached
	}
	memset(red,0,8);
	memset(green,0,8);
	memset(blue,0,8);
	send_leds(red, green, blue);	// Write
	return;
}
#endif

// Initiailize the system
void system_init(void)
{
	// Remove System Clock Division
	CCP = 0xD8;
	CLKPSR = 0x00;

	// Enable LED Output Pins
	LED_DATA_PORT &= ~_BV(LED_DATA_PIN);	// Set output to zero first
	LED_DATA_DIR |= _BV(LED_DATA_PIN);	// LED TX line - need to be an output

	// Enable LED Output MOSFET
	LED_EN_PORT &= ~_BV(LED_EN_PIN);
	LED_EN_DIR |= _BV(LED_EN_PIN);
	LED_EN_PORT |= _BV(LED_EN_PIN);

	// Initialize bit-bang i2c and activate accelerometer
	i2c_init();

	i2c_start_wait((MMA7660_ADR << 1) + I2C_WRITE);
	i2c_write(0x07);	// Set Device in active Mode
	i2c_write(0x01);	// Write active mode bit
	i2c_stop();

	return;
}
