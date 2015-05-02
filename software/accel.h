#ifndef __accel_h__
#define __accel_h__

#define MMA7660_ADR 0x4C

#define ACCEL_X_AXIS	0x00	// X Output
#define ACCEL_Y_AXIS	0x01	// Y Output
#define ACCEL_Z_AXIS	0x02	// Z Output
#define ACCEL_TILT		0x03	// Tilt Status (Read only)
#define ACCEL_SRST		0x04	// Sample Rate Status Register (Read only)
#define ACCEL_SPCNT		0x05	// Sleep Count Register (Read/Write)
#define ACCEL_INTSU		0x06	// Interrupt Setup Register
#define ACCEL_MODE		0x07	// Mode Register (Read/Write)
#define ACCEL_SR		0x08	// Sample Rate Register
#define ACCEL_PDET		0x09	// Tap/Pulse Detection Register (Read/Write)
#define ACCEL_FD		0x0A	// Tap/Pulse Debounce Count Register (R/W)

typedef enum {ORIENT_L, ORIENT_R, ORIENT_F, ORIENT_B, ORIENT_UK} ORIENTATION_T;

// Reads the value from the give register within the accelerometer
uint8_t accel_reg_read(uint8_t addr);

// Return the average value of the given axis (8 iterations)
int8_t axis_average(uint8_t axis);

// Determine the current orientation from accelerometer
ORIENTATION_T accel_get_orientation(void);

// Debounce orientation detection
ORIENTATION_T accel_confirm_orientation(ORIENTATION_T orientation, uint8_t threshold);

#endif // __accel_h__
