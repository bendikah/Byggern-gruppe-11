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
  joystick_init();
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
  char user_1[] = {'e','i','v'};
  char user_2[] = {'r','o','b'};
  save_user(0,user_1);
  save_user(1,user_2);

/*oled_sram_clear_screen();
  int u = 333;
  char streng[4];// = {0,0,0};
  sprintf(streng, "%d", u);

  for (int i = 0; i < (uint8_t)ceil(log10(u)); i++){
    oled_sram_put_char(streng[i]);
  }
  oled_sram_update();*/
//_delay_ms(3000);

  /*
  save_user(1,user_1);
  oled_sram_clear_screen();
  save_high_score(0,"eiv",254);
  save_high_score(1,"rob",10);
  save_high_score(2,"ben",7);
  save_high_score(3,"eiv",4);
  save_high_score(4,"ben",1);
  */
  /*
  oled_sram_clear_screen();
  oled_sram_print("Halla\n");
  oled_sram_print("Hva skjer\n");
  oled_sram_print("Io man!\n");

  */

  /*
  for (int i = 0; i < 25;i++){
    oled_sram_shift_whole_shit_one_bit();
    oled_sram_update();
    _delay_ms(40);
  }
  */
  draw_page_credits_better();
  oled_sram_update();
  _delay_ms(5000);
  //add_user(1);

  //test_menu();


  struct Joystick_positions joystick_positions;
/*
  while(1){
      joystick_positions = joystick_read_positions();

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
      USART_printf("Shits happening %d \n", joystick_positions.y);
  }
*/
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
