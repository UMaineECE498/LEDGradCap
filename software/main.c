
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "system.h"
#include "i2cmaster.h"

int grad_cap_mode(void);
void do_grad_cap(void);
void change_leds(uint8_t step);
uint8_t read_accel(void);
void do_shaky_shaky(void);
uint8_t tilted_to_left(void);
// Initialize the system
void system_init(void);

#define NUM_LOOPS 10 //number of loops
#define MAX_STEPS 5  //

int main(void)
{
	uint8_t red[8]={0};
	uint8_t green[8]={0};
	uint8_t blue[8]={0};

	system_init();
#if 0
	blue[0]=10;
	blue[1]=10;
	red[2]=10;
	red[3]=10;
	blue[4]=10;
	blue[5]=10;
	red[6]=10;
	red[7]=10;
#endif

	while(1)
	{
		int ret = i2c_start((MMA7660_ADR << 1) + I2C_WRITE);

		ret = i2c_write(0x00); 		// Set to read from x axis register
		i2c_rep_start((MMA7660_ADR << 1) + I2C_READ);
		blue[0] = i2c_readNak();		// Read Value
		blue[0]=blue[0]&0x1f;
		if (blue[0]>15) {
			red[0]=31-blue[0];
			blue[0]=0;
		} else {
			red[0]=0;
		}
		i2c_stop();

		send_leds(&red,&green,&blue);
		_delay_ms(10);
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
void system_init(void)
{
	// Remove System Clock Division
	CCP = 0xD8;
	CLKPSR = 0x00;

	// Enable LED Output Pins
	LED_DATA_PORT &= ~_BV(LED_DATA_PIN);	// Set output to zero first
	LED_DATA_DIR |= _BV(LED_DATA_PIN);    // LED TX line - need to be an output

	// Enable LED Output MOSFET
	LED_EN_PORT &= ~_BV(LED_EN_PIN);
	LED_EN_DIR |= _BV(LED_EN_PIN);
	LED_EN_PORT |= _BV(LED_EN_PIN);

	// Initialize bit-bang i2c and activate accelerometer
	i2c_init();

	i2c_start_wait((MMA7660_ADR << 1) + I2C_WRITE);
	i2c_write(0x07); 		// Set Device in active Mode
	i2c_write(0x01);		// Write active mode bit
	i2c_stop();


	return;
}
