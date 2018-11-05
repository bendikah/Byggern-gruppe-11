#include "global_defines.h"
#include "test.h"
#include "breadboard_input.h"

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "util/delay.h"
#include "can.h"
#include "menu.h"

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

void test_can(void){
	can_init(1);

	can_message msg;
  msg.id = 1;
  msg.length = 3;
  msg.data[0] = 7;
  msg.data[1] = 2;
  msg.data[2] = 0;

	USART_printf("CAN TEST STARTING");

  can_message new_msg;
  int i = 0;
  while(1){
    msg.data[2] = i;
    i++;
    can_transmit(&msg);
    _delay_ms(2000);

    can_recieve(&new_msg);
    USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    for(int i = 0; i < new_msg.length; i++){
  		  USART_printf(", %x", new_msg.data[i]);
  	}
		USART_printf("\n");
}
}

void test_mcp(){
	//mcp_write(MCP_TXB0CTRL,0xFF); ??
	spi_initialize();
	mcp_reset();
	while(1){
		_delay_ms(2000);
		mcp_write(0x03, 0x7D);
		uint8_t ret = mcp_read(0x03);
		USART_printf("%x",ret);
	}
	uint8_t readval = mcp_status();
	USART_printf("this is the shit from mcp %x",readval);
}

void test_menu(void){
	menu_init();
	joystick_init();
	struct Joystick_positions joystick_positions;

	while(1){
		joystick_positions = joystick_read_positions();
		USART_printf("this is the value y = %02d \n", joystick_positions.y);
		if (joystick_positions.y >= 40){
			menu_decrement_branch();
		}
		else if (joystick_positions.y <= -40){
			menu_increment_branch();
		}
		if (joystick_read_button()){
			menu_next_page();
		}
		_delay_ms(1000);
	}
}
