#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#include "system.h"
#include "ledRoutines.h"
#include "led.h"

uint8_t i, r, g, b;

void send_all(uint8_t r, uint8_t g, uint8_t b) {
	memset(red,r,8);
	memset(green,g,8);
	memset(blue,b,8);
	send_leds(red,green,blue);
	_delay_ms(FADE_DELAY);
}

void fadecolor(uint8_t rinc, uint8_t ginc, uint8_t binc) {
	for (i=0;i<64;i++) {
		if (i&0x01) {
			r += rinc;
			g += ginc;
			b += binc;
		}
		send_all(r,g,b);
	}
} 

void myfade(void)
{


	r=64;
	g=64;
	b=64;
	fadecolor(-1, -1, -1);
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
	fadecolor(1, 1, 1);
	fadecolor(-1, -1, 0);
	fadecolor(1, 1, 0);
	// for (i=0;i<64;i++) {
	// 	r--;
	// 	g--;
	// 	memset(red,r,8);
	// 	memset(green,g,8);
	// 	memset(blue,b,8);
	// 	send_leds(red,green,blue);
	// 	_delay_ms(FADE_DELAY);
	// }
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







