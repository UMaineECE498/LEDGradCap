#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#include "system.h"
#include "ledRoutines.h"
#include "led.h"




void myfade(void)
{
 	uint8_t i, r, g, b;

 	r=64;
 	g=64;
 	b=64;
 	for (i=0;i<64;i++) {
 		if (i&0x01) r--;
 		if (i&0x01) g--;
 		if (i&0x01) b--;
 		memset(red,r,8);
 		memset(green,g,8);
 		memset(blue,b,8);
 		send_leds(red,green,blue);
 		_delay_ms(FADE_DELAY);
 	}
 	for (i=0;i<64;i++) {
 		if (i&0x01) r++;
 		if (i&0x01) g++;
 		if (i&0x01) b++;
 		memset(red,r,8);
 		memset(green,g,8);
 		memset(blue,b,8);
 		send_leds(red,green,blue);
 		_delay_ms(FADE_DELAY);
 	}
 	for (i=0;i<64;i++) {
 		r--;
 		g--;
 		memset(red,r,8);
 		memset(green,g,8);
 		memset(blue,b,8);
 		send_leds(red,green,blue);
 		_delay_ms(FADE_DELAY);
 	}
 	for (i=0;i<64;i++) {
 		r++;
 		g++;
 		memset(red,r,8);
 		memset(green,g,8);
 		memset(blue,b,8);
 		send_leds(red,green,blue);
 		_delay_ms(FADE_DELAY);
 	}
 }





 
	
