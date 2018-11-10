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

int main(void){
  //DDRA = 0xFF;
  USART_Init ( MYUBRR );
  set_bit(MCUCR,SRE);
  //set_bit(MCUCR, ISC01);
  //fdevopen(USART_Transmit, USART_Receive);
  //joystick_init();
  //SRAM_test();
	oled_sram_initialize();
//_delay_ms(5000);
  //SRAM_test();
  //testThisShit();
  //test_adc();
  //oled_sram_print("hello world");
//menu_init();
//reboot();
  USART_printf("STARTING \n");



  //can_init(1);

  /*
  oled_sram_fill_screen();
  oled_sram_update();
  _delay_ms(500);
  oled_sram_clear_screen();
  oled_sram_update();
  //testing interrupt
  //interrupt_init();
  */
  //testing can
  //test_can();

  USART_printf("test Motor\n");
  can_init(1);
  joystick_init();
  //Servo test
  _delay_ms(2000);
  can_transmit(&msg_game_start);
  while(1){
  _delay_ms(50);
  joy_send_pos();
  }



}
