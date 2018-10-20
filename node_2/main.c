#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

#include "spi.h"
#include "can.h"
#include "global_defines.h"

#include "util/delay.h"
#include "pwm.h"
#include "servo_driver.h"

int main(void){
    USART_Init ( MYUBRR );
    set_bit(MCUCR,SRE);
    spi_initialize();
    //mcp_reset();
    /*while(1){
        /*set_bit(PORTB,SS);
        _delay_ms(1000);
        clear_bit(PORTB,SS);
        _delay_ms(1000);
        //mcp_reset();

        _delay_ms(2000);
        mcp_write(0x03, 0xD0);
        uint8_t ret = mcp_read(0x03);
        USART_printf("%x\n",ret);
    }

  */
  //can_init(0);


  /*can_message msg;
  msg.id = 1;
  msg.length = 3;
  msg.data[0] = 1;
  msg.data[1] = 2;
  msg.data[2] = 3;*/
  USART_printf("CAN TEST STARTING \n");
  //can_init(1);
  pwm_init();
  servo_set_angle(-100);
  int i = 0;
  while(1){

    _delay_ms(2000);
    /*can_recieve(&new_msg);
    USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    for(int i = 0; i < new_msg.length; i++){
  		  USART_printf(", %x", new_msg.data[i]);
  	}*/
    USART_printf("ting skjer\n");







    }


}
