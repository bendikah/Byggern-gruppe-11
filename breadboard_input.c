
#include "breadboard_input.h"
#include "adc.h"

#define LEFT_SLIDER		CHANNEL_1
#define RIGHT_SLIDER	CHANNEL_2
#define X_AXIS			CHANNEL_3
#define Y_AXIS			CHANNEL_4

uint8_t read_joystick_x(void){
	return read_adc(X_AXIS);
}

uint8_t read_joystick_y(void){
	return read_adc(Y_AXIS);
}

uint8_t read_left_slider(void){
	return read_adc(LEFT_SLIDER);
}
uint8_t read_right_slider(void){
	return read_adc(RIGHT_SLIDER);
}