// A. Sheaff 1/24/2015
// ECE 498 Grad Cap led header
#ifndef LED_H
#define LED_H
#include <stdint.h>

void led_test();
// Send 8, 24 bit "frames" to 8 leds.
// ra contains ! 8 ! red values
// rb contains ! 8 ! green values
// rc contains ! 8 ! blue values
void send_leds(uint8_t *ra, uint8_t *ga, uint8_t *ba);

#endif // LED_H
