#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

#include "spi.h"
#include "can.h"
#include "global_defines.h"

#include "util/delay.h"


int main(void){
  USART_Init ( MYUBRR );
  set_bit(MCUCR,SRE);
  spi_initialize();
  can_init(1);

  can_message msg;
  msg.id = 1;
  msg.length = 3;
  msg.data[0] = 1;
  msg.data[1] = 2;
  msg.data[2] = 3;
  USART_printf("CAN TEST STARTING");
  can_init(1);

  can_message new_msg;
  while(1){
    //can_transmit(&msg);
    _delay_ms(2000);
    new_msg = can_recieve();
    USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    for(int i = 0; i < msg.length; i++){
  		  USART_printf(", %x", msg.data[i]);
  	}
    USART_printf("\n");
  }
}
