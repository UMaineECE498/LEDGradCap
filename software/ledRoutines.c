#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#include "system.h"
#include "ledRoutines.h"
#include "led.h"

static uint8_t i, r, g, b;

void fadecolor(int8_t rinc, int8_t ginc, int8_t binc)
{
	for (i=1;i<64;i++)
	{
		r += rinc;
		g += ginc;
		b += binc;

		memset(red,r,8);
		memset(green,g,8);
		memset(blue,b,8);
		send_leds(red,green,blue);
		_delay_ms(FADE_DELAY);
	}
} 

void rgbfade(void)
{

	r=0;
	g=0;
	b=0;
	//fade from _+_+_ => R+G+B
	fadecolor(1, 1, 1);

	//fade  => R+_+B
	fadecolor(0, -1, 0);

	//fade  => _+_+B
	fadecolor(-1, 0, 0);

	//fade  => _+G+B
	fadecolor(0, 1, 0);

	//fade  => R+G+B
	fadecolor(1, 0, 0);

	//fade  => R+G+_
	fadecolor(0, 0, -1);

	//fade  => R+_+_
	fadecolor(0, -1, 0);

	//fade  => R+_+B
	fadecolor(0, 0, 1);

	//fade  => R+G+B
	fadecolor(0, 1, 0);

	//fade  => _+G+B
	fadecolor(-1, 0, 0);

	//fade  => _+G+_
	fadecolor(0, 0, -1);

	//fade  => R+G+_
	fadecolor(1, 0, 0);

	//fade  => R+G+B
	fadecolor(0, 0, 1);

	//fade white to off
	fadecolor(-1, -1, -1);

}

void bwfade(void) {
	r=0;
	g=0;
	b=0;
	//fade from _+_+_ => R+G+B
	fadecolor(1, 1, 1);

	//fade  => _+_+B
	fadecolor(-1, -1, 0);

	//fade  => R+G+B
	fadecolor(1, 1, 0);

	//fade  => _+_+_
	fadecolor(-1, -1, -1);

}





