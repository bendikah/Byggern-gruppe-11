#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

#include "spi.h"
#include "can.h"
#define F_CPU 16000000

#include "util/delay.h"
//#define FOSC 1968500// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )


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
