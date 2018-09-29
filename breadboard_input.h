
#ifndef BREADBOARD_INPUT_H
#define BREADBOARD_INPUT_H


#include <stdint.h>

enum Direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};

struct Joystick_positions {
	uint8_t x;
	uint8_t y;
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
enum Direction joystick_get_direction();

int joystick_read_x(void);
int joystick_read_y(void);
int joystick_read_button(void);

uint8_t slider_read_left(void);
uint8_t slider_read_right(void);


#endif
