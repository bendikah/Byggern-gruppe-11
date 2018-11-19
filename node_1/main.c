#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "test_sram.h"
#include "menu.h"
#include "global_defines.h"
#include "util/delay.h"
#include "breadboard_input.h"
#include "can.h"
#include "test.h"
#include "sram.h"
#include "mcp_driver.h"

#include "can_handler.h"
#include "joy_can.h"
#include <avr/interrupt.h>
#include "can_messages.h"

#include "oled_sram.h"
#include "spi.h"
#include "load_and_save.h"
#include "eeprom.h"
#include "snake_game.h"
#include "pingpong.h"

int main(void){

  USART_Init ( MYUBRR );
  set_bit(MCUCR,SRE);
	oled_sram_initialize();
  can_init(1);
  can_handler_init();
  joystick_init();
	menu_init();

	struct Joystick_positions joystick_positions;

	while(1){
		joystick_positions = joystick_read_positions();
		if (joystick_positions.y >= 40){
			menu_decrement_branch();
		}
		else if (joystick_positions.y <= -40){
			menu_increment_branch();
		}
		if (right_touch_button_read()){
			menu_next_page();
		}
		_delay_ms(1000);
	}

}
