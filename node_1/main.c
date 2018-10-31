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

#include "interrupt.h"
#include "joy_can.h"
#include <avr/interrupt.h>
#include "oled_sram.h"
#include "spi.h"
#include "oled.h"

int main(void){
  //DDRA = 0xFF;
  USART_Init ( MYUBRR );
  set_bit(MCUCR,SRE);
  //set_bit(MCUCR, ISC01);
  //fdevopen(USART_Transmit, USART_Receive);
  //joystick_init();
  SRAM_test();
	//oled_sram_initialize();
  oled_initialize();
//_delay_ms(5000);
  //SRAM_test();
  //testThisShit();
  //test_adc();
  USART_printf("STARTING \n");
  //oled_sram_print("hello world");
  menu_init();
  //can_init(1);
  /*oled_goto_line(0);
  for (int i = 0; i < 8; i++){
    oled_clear_screen();
    oled_goto_line(0);
    oled_goto_column(0);
    oled_print_up_shifted("Hallo", i);
    _delay_ms(400);
  }*/

  //oled_printf("hallo");

  //github solution mcp
  /*
  while(1){
    _delay_ms(2000);
  mcp2515_init();
  }
  */
  // our mcp_driver

  //mcp_write(MCP_TXB0CTRL,0xFF);
  /*spi_initialize();
  mcp_reset();
  while(1){
    _delay_ms(2000);
    mcp_write(0x03, 0x7D);
    uint8_t ret = mcp_read(0x03);
    USART_printf("%x",ret);
  }
  uint8_t readval = mcp_status();
  USART_printf("this is the shit from mcp %x",readval);

  */


  //testing interrupt
  //interrupt_init();

  //testing can
  //test_can();

  //USART_printf("test Servo\n");
  //can_init(1);
  //joystick_init();
  //Servo test
  while(1){
  _delay_ms(1000);
  //joy_send_pos();
  }

}
