
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int grad_cap_mode(void);
void do_grad_cap(void);

#define NUM_LOOPS 10 //number of loops
#define MAX_STEPS 5  //

int main(void)
{
	//initialize_everything();
	while(1) {
		if(grad_cap_mode()) {
			do_grad_cap();
		}
		else {
			do_shaky_shaky();
		}
	}
	return 0;
}

// if Z~=1G I'm Flat
// if Z~=0 I'm Shaky Shaky
int grad_cap_mode(void)
{
	//read_accel();
	if(z > .5)
		return 1;
	return 0;
}

void do_grad_cap(void)
{
	int step = 0;
	int loops = 0;

	while(grad_cap_mode())
	{
		if(loops<NUM_LOOPS)
		{
			change_leds(step);
		}
		step++;
		if(step>MAX_STEPS) {
			step = 0;
			loops ++;
		}

		if (titled_to_left())
		{
			step = 0;
			loops = 0;
		}
		//@todo determine the best delay, sleep?
		_delay_ms(100);
	}
}

//detect a clap show a flash of Maine Blue