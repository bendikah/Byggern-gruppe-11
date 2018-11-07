#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "test_sram.h"
#include "oled.h"
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

#include "spi.h"

int main(void){
  //DDRA = 0xFF;
  USART_Init ( MYUBRR );
  set_bit(MCUCR,SRE);
  //set_bit(MCUCR, ISC01);
  //fdevopen(USART_Transmit, USART_Receive);
  //joystick_init();

	oled_initialize();
//_delay_ms(5000);
  SRAM_test();
  //testThisShit();
  //test_adc();
//menu_init();
  can_init(1);
  USART_printf("STARTING \n");
  _delay_ms(5000);
  can_transmit(&msg_game_start);
  /*while (1) {
    USART_printf("kjorer \n");
    _delay_ms(5000);
  }*/
  //test_can();
  //can_init(1);



  //testing interrupt
  //can_handler_init();

  //testing can
  //test_can();

  USART_printf("test Motor\n");
  can_init(1);
  joystick_init();
  //Servo test
  while(1){
  _delay_ms(100);
  joy_send_pos();
  }

}
