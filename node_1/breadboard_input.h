
#ifndef BREADBOARD_INPUT_H
#define BREADBOARD_INPUT_H


#include <stdint.h>


struct Joystick_positions {
	int8_t x;
	int8_t y;
};

struct Joystick_offsets {
	uint8_t x_max;
	uint8_t x_min;
	uint8_t x_neutral;
	uint8_t y_max;
	uint8_t y_min;
	uint8_t y_neutral;
};

void joystick_init();
void joystick_calibrate();

struct Joystick_positions joystick_read_positions();

int joystick_read_x(void);
int joystick_read_y(void);
uint8_t joystick_read_button(void);

uint8_t slider_read_left(void);
uint8_t slider_read_right(void);
uint8_t right_touch_button_read(void);

#endif
