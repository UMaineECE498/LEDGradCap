#if 0
#include "shaky.h"

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