#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#include "system.h"
#include "ledRoutines.h"
#include "led.h"

static uint8_t i, r, g, b;

void fadecolor(int8_t rinc, int8_t ginc, int8_t binc, int8_t rstep, int8_t gstep, int8_t bstep)
{
	for (i=0;i<64;i++)
	{
		if (i&rstep)
			r += rinc;
		if (i&gstep)
			g += ginc;
		if (i&bstep)
			b += binc;

		memset(red,r,8);
		memset(green,g,8);
		memset(blue,b,8);
		send_leds(red,green,blue);
		_delay_ms(FADE_DELAY);
	}
} 

void myfade(void)
{


	r=64;
	g=64;
	b=64;
	fadecolor(-1, -1, -1, 0x01, 0x01, 0x01);
	// for (i=0;i<64;i++) {
	// 	if (i&0x01) {
	// 		r--;
	// 		g--;
	// 		b--;
	// 	}
	// 	memset(red,r,8);
	// 	memset(green,g,8);
	// 	memset(blue,b,8);
	// 	send_leds(red,green,blue);
	// 	_delay_ms(FADE_DELAY);
	// }
	fadecolor(1, 1, 1, 0x01, 0x01, 0x01);
	// for (i=0;i<64;i++) {
	// 	if (i&0x01) {
	// 		r++;
	// 		g++;
	// 		b++;
	// 	}
	// 	memset(red,r,8);
	// 	memset(green,g,8);
	// 	memset(blue,b,8);
	// 	send_leds(red,green,blue);
	// 	_delay_ms(FADE_DELAY);
	// }
	
	fadecolor(-1, -1, 0);
	// for (i=0;i<64;i++) {
	// 	r--;
	// 	g--;
	// 	memset(red,r,8);
	// 	memset(green,g,8);
	// 	memset(blue,b,8);
	// 	send_leds(red,green,blue);
	// 	_delay_ms(FADE_DELAY);
	// }
	fadecolor(1, 1, 0);
	// for (i=0;i<64;i++) {
	// 	r++;
	// 	g++;
	// 	memset(red,r,8);
	// 	memset(green,g,8);
	// 	memset(blue,b,8);
	// 	send_leds(red,green,blue);
	// 	_delay_ms(FADE_DELAY);
	// }
}







