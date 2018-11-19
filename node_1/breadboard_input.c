#include "global_defines.h"
#include "breadboard_input.h"
#include "adc.h"
#include "uart.h"
#include <stdio.h>
#include <avr/io.h>
#include "oled_sram.h"
#include "util/delay.h"


#define JOYSTICK_CALIBRATE

#define LEFT_SLIDER		CHANNEL_1
#define RIGHT_SLIDER		CHANNEL_2
#define X_AXIS			CHANNEL_3
#define Y_AXIS			CHANNEL_4
#define BUTTON_PORT	PORTB
#define JOYSTICK_BUTTON_PIN		1
#define TOUCH_BUTTON_RIGHT 2
#define TOUCH_BUTTON_LEFT 3


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
	//Initialize joy_button
	clear_bit( DDRB, 1 );
	set_bit(BUTTON_PORT, 1);

	//Initialize touch buttons
	clear_bit(DDRB, TOUCH_BUTTON_RIGHT);
	set_bit(BUTTON_PORT, TOUCH_BUTTON_RIGHT);
	clear_bit(DDRB, TOUCH_BUTTON_LEFT);
	set_bit(BUTTON_PORT, TOUCH_BUTTON_LEFT);
	#ifdef JOYSTICK_CALIBRATE
	joystick_calibrate();
	#endif
}

void joystick_calibrate()
{
	oled_sram_print("joy up");// Joystick - move joystick to TOP, then press the right button:\n");
	oled_goto_column(0);
	oled_goto_line(1);
	oled_sram_print("& push but");

	oled_sram_update();
	while(!right_touch_button_read()){};

	joystick_offsets.y_max = adc_read(Y_AXIS);

	_delay_ms(2000);
	oled_goto_column(32);
	oled_sram_print("right");// Joystick - move joystick to RIGHT, then press the right button:\n");
	oled_sram_update();

	while(!right_touch_button_read()){};

	joystick_offsets.x_max = adc_read(X_AXIS);	_delay_us(1000);

_delay_ms(2000);
oled_goto_column(32);
	oled_sram_print("left ");// Joystick - move joystick to LEFT, then press the right button:\n");
	oled_sram_update();

	while(!right_touch_button_read()){};

	joystick_offsets.x_min = adc_read(X_AXIS);

	_delay_ms(2000);
	oled_goto_column(32);
	oled_sram_print("down  ");// Joystick - move joystick to BOTTOM, then press the right button:\n");
	oled_sram_update();

	while(!right_touch_button_read()){};

	joystick_offsets.y_min = adc_read(Y_AXIS);

	_delay_ms(2000);
	oled_goto_column(32);
	oled_sram_print("mid  ");
	oled_sram_update();

	while(!right_touch_button_read()){};
	joystick_offsets.x_neutral = adc_read(X_AXIS);
	joystick_offsets.y_neutral = adc_read(Y_AXIS);
	USART_printf("Offsets");// calculated to be: x.neutral = %d, y.neutral = %d.\n\n", joystick_offsets.x_neutral, joystick_offsets.y_neutral);

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

uint8_t right_touch_button_read(void){
	return !!((PINB & (1 << TOUCH_BUTTON_RIGHT)));
}
uint8_t left_touch_button_read(void){
	return !!((PINB & (1 << TOUCH_BUTTON_LEFT)));
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
