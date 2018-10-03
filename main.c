#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "test_sram.h"
#include "oled.h"
#include "menu.h"
#define F_CPU 4915200
#include "util/delay.h"
#include "breadboard_input.h"

#include "test.h"

//#define FOSC 1968500// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )


int main(void){
  //DDRA = 0xFF;
  USART_Init ( MYUBRR );
  set_bit(MCUCR,SRE);
  //set_bit(MCUCR, ISC01);
  //fdevopen(USART_Transmit, USART_Receive);
  joystick_init();

	oled_initialize();
//_delay_ms(5000);
  SRAM_test();
  //testThisShit();
  //test_adc();
	struct Joystick_positions joy_pos;
	menu_init();

	while(1){
		joy_pos = joystick_read_positions();
    USART_printf("ting gårfremover y: %d og x: %d\n",joy_pos.y, joy_pos.x);
		if (joy_pos.y >= 50){
			menu_decrement_branch();
			USART_printf("Ting skjer de\n");

		} else if (joy_pos.y <= -50){
			menu_increment_branch();
			USART_printf("Ting skjer in\n");
		}
		if (joystick_read_button() == 1){
			int variabel = get_menu_branch();
			USART_printf("Dette funker? %d\n",variabel);
		}
		_delay_ms(500);
		//printf("y-pos: %d\n", joy_pos.y);
		USART_printf("ting gårfremover2 y: %d og x: %d\n",joy_pos.y, joy_pos.x);
	};
}
