#include "global_defines.h"
#include "breadboard_input.h"
#include "adc.h"
#include "uart.h"
#include <stdio.h>
#include <avr/io.h>


//#define JOYSTICK_CALIBRATE

#define LEFT_SLIDER		CHANNEL_1
#define RIGHT_SLIDER		CHANNEL_2
#define X_AXIS			CHANNEL_3
#define Y_AXIS			CHANNEL_4
#define JOYSTICK_BUTTON_PORT	PORTB
#define JOYSTICK_BUTTON_PIN		0


static struct Joystick_positions joystick_positions;
static struct Joystick_offsets joystick_offsets;

void joystick_init()
{
	joystick_offsets.x_neutral = 128;
	joystick_offsets.x_max = 255;
	joystick_offsets.x_min = 0;

	joystick_offsets.y_neutral = 128;
	joystick_offsets.y_max = 255;
	joystick_offsets.y_min = 0;

	clear_bit( DDRB, 1 );
	set_bit( JOYSTICK_BUTTON_PORT, 1);

	#ifdef JOYSTICK_CALIBRATE
	joystick_calibrate();
	#endif
}

void joystick_calibrate()
{
	/*printf("Calibrating Joystick - move joystick to TOP, then press the right button:\n");
	while(!test_bit(PINB, rightButton)){};

	ADC_read(channelX);

	_delay_us(1000);
	OFFSETS.y_max = POSITION.y;
	_delay_ms(500);

	printf("Good job! value at TOP position: Y = %d\n\n", OFFSETS.y_max);

	printf("Calibrating Joystick - move joystick to RIGHT, then press the right button:\n");
	while(!test_bit(PINB, rightButton)){};

	ADC_read(channelX);
	_delay_us(1000);
	OFFSETS.x_max = POSCSITION.x;

	_delay_ms(500);
	printf("Good job! value at RIGHT position: X = %d\n\n", OFFSETS.x_max);

	printf("Calibrating Joystick - move joystick to LEFT, then press the right button:\n");
	while(!test_bit(PINB, rightButton)){};

	ADC_read(channelX);
	_delay_us(1000);
	OFFSETS.x_min = POSITION.x;

	_delay_ms(500);
	printf("Good job! value at LEFT position: X = %d\n\n", OFFSETS.x_min);

	printf("Calibrating Joystick - move joystick to BOTTOM, then press the right button:\n");
	while(!test_bit(PINB, rightButton)){};

	ADC_read(channelX);
	_delay_us(1000);
	OFFSETS.y_min = POSITION.y;

	_delay_ms(500);
	printf("Good job! value at BOTTOM position: Y = %d\n\n", OFFSETS.y_min);

	OFFSETS.x_neutral = (OFFSETS.x_max + OFFSETS.x_min)/2;
	OFFSETS.y_neutral = (OFFSETS.y_max + OFFSETS.y_min)/2;
	printf("Offsets calculated to be: x.neutral = %d, y.neutral = %d.\n\n", OFFSETS.x_neutral, OFFSETS.y_neutral);
	*/
}

struct Joystick_positions joystick_read_positions(){
	joystick_positions.x = joystick_read_x();
	joystick_positions.y = joystick_read_y();
	return joystick_positions;
}


int joystick_read_x(void){
	int out = adc_read(X_AXIS);
	if (out > joystick_offsets.x_neutral){
		return (1-(float)((joystick_offsets.x_max - out))/(joystick_offsets.x_max - joystick_offsets.x_neutral))*100;
	}
	return -(1-(float)((joystick_offsets.x_min - out))/(joystick_offsets.x_min - joystick_offsets.x_neutral))*100;
}

int joystick_read_y(void){
	int out = adc_read(Y_AXIS);
	if (out > joystick_offsets.y_neutral){
		return (1-(float)((joystick_offsets.y_max - out))/(joystick_offsets.y_max - joystick_offsets.y_neutral))*100;
	}
	return -(1-(float)((joystick_offsets.y_min - out))/(joystick_offsets.y_min - joystick_offsets.y_neutral))*100;
}

uint8_t joystick_read_button(void){
	/*int joy_new_button_value = !test_bit( JOYSTICK_BUTTON_PORT, JOYSTICK_BUTTON_PIN );
	if (joy_new_button_value && !joy_last_button_value){
		joy_last_button_value = joy_new_button_value;
		return joy_new_button_value;
	}
	if (!joy_new_button_value && joy_last_button_value){
		joy_last_button_value = joy_new_button_value;
		return joy_new_button_value;
	}
	return 0;*/
	uint8_t i = !((PINB & (1 << 1)));
	//uint8_t i = !! test_bit( JOYSTICK_BUTTON_PORT, JOYSTICK_BUTTON_PIN );

	return i;
}

uint8_t slider_read_left(void){
	return adc_read(LEFT_SLIDER);
}
uint8_t slider_read_right(void){
	return adc_read(RIGHT_SLIDER);
}
