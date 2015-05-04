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

void myfade(void)
{


	r=0;
	g=0;
	b=0;
	//fade from off to full white
	fadecolor(1, 1, 1);

	//fade from white to G+B
	fadecolor(0, -1, 0);

	//fade from G+B => B
	fadecolor(-1, 0, 0);

	//fade from B => B+R
	fadecolor(0, 1, 0);

	//fade from B+R => R+G+B (White)
	fadecolor(1, 0, 0);

	//fade from white to R+G
	fadecolor(0, 0, -1);

	//fade from R+G => R
	fadecolor(0, -1, 0);

	//fade from R => R+B
	fadecolor(0, 0, 1);

	//fade from B+R => R+G+B (White)
	fadecolor(0, 1, 0);

	//fade from white to R+G
	fadecolor(-1, 0, 0);

	//fade from R+G => R
	fadecolor(0, 0, -1);

	//fade from R => R+B
	fadecolor(1, 0, 0);

	//fade from B+R => R+G+B (White)
	fadecolor(0, 0, 1);

	//fade from white to off
	fadecolor(-1, -1, -1);



}







