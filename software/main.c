
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int grad_cap_mode(void);
void do_grad_cap(void);
void change_leds(uint8_t step);
uint8_t read_accel(void);
void do_shaky_shaky(void);
uint8_t tilted_to_left(void);
// Initialize the system
void init(void);

#define NUM_LOOPS 10 //number of loops
#define MAX_STEPS 5  //

int main(void)
{
	uint8_t red[8]={0};
	uint8_t green[8]={0};
	uint8_t blue[8]={0};

	PORTA &= ~_BV(PIN4);
	DDRA |= _BV(PIN4);
	PORTA |= _BV(PIN4);


	init();
	blue[1]=20;
	send_leds(&red,&green,&blue);
	while(1)
	{

	}
	// while(1) {
	// 	if(grad_cap_mode()) {
	// 		do_grad_cap();
	// 	}
	// 	else {
	// 		do_shaky_shaky();
	// 	}
	// }
	return 0;
}

// if Z~=1G I'm Flat
// if Z~=0 I'm Shaky Shaky
int grad_cap_mode(void)
{
	uint8_t z=0;

	z=read_accel();
	if(z > .5) {
		return 1;
	}
	return 0;
}

void do_grad_cap(void)
{
	int step = 0;
	int loops = 0;

	while(grad_cap_mode()) {
		if(loops<NUM_LOOPS) {
			change_leds(step);
		}
		step++;
		if(step>MAX_STEPS) {
			step = 0;
			loops ++;
		}

		if (tilted_to_left()) {
			step = 0;
			loops = 0;
		}
		//@todo determine the best delay, sleep?
		_delay_ms(100);
	}
}

//detect a clap show a flash of Maine Blue

void change_leds(uint8_t step)
{
	return;
}


uint8_t read_accel(void)
{
	return 0;
}

void do_shaky_shaky(void)
{
	return;
}
uint8_t tilted_to_left(void)
{
	return 0;
}

// Initiailize the system
void init(void)
{
	PORTA&=~_BV(PIN3);	// Set output to zero first
	DDRA|=_BV(PIN3);    // LED TX line - need to be an output
	return;
}
