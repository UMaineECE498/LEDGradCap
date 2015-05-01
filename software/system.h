#ifndef __system_h__
#define __system_h__

#include <avr/io.h>

#define LED_DATA_PORT 	PORTA
#define LED_DATA_DIR	DDRA
#define LED_DATA_PIN	PIN3

#define LED_EN_PORT		PORTA
#define LED_EN_DIR		DDRA
#define LED_EN_PIN	PIN4

#endif	// __system_h__
