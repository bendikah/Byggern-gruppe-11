#include "global_defines.h"
#include "test.h"
#include "breadboard_input.h"

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "util/delay.h"


void testThisShit(void){
	DDRA = 0xFF;
	set_bit(PORTA,6);

}

void test_adc(void){
	//struct Joystick_positions joystick_positions;
	joystick_init();
	int out;
	while(1){
		out = joystick_read_x();


		/*joystick_positions = joystick_read_positions();
		uint8_t l_slider = slider_read_left();
		uint8_t r_slider = slider_read_right();
		printf("this is the values x = %02X y = %02X L_slider = %02X and R_slider = %02X \n",joystick_positions.x,joystick_positions.y,l_slider,r_slider);*/
		printf("this is the value x = %02d \n", out);
		_delay_ms(500);
	}
}

void test_latch(void){
	DDRA = 0xFF;
	set_bit(DDRE, 1);
	PORTA = 0xFF;
	set_bit(PORTE,1);
	_delay_ms(2000);
	clear_bit(PORTE,1);
	PORTA = 0;
	_delay_ms(5000);
	set_bit(PORTE,1);

}
