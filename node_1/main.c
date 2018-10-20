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
  USART_printf("STARTING \n");
  oled_sram_print("hello world");

  can_init(1);

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

  can_init(1);
  can_message msg;
  msg.id = 1;
  msg.length = 3;
  msg.data[0] = 7;
  msg.data[1] = 2;
  msg.data[2] = 0xC;
  USART_printf("CAN TEST STARTING");

  can_message new_msg;
  int i = 0;
  while(1){
    msg.data[2] = i;
    i++;
    can_transmit(&msg);
    _delay_ms(2000);
    /*
    can_recieve(&new_msg);
    USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    for(int i = 0; i < new_msg.length; i++){
  		  USART_printf(", %x", new_msg.data[i]);
  	}
    */
    USART_printf("test\n");
  }

}
