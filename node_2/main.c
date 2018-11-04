#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

#include "spi.h"
#include "can.h"
#include "global_defines.h"

#include "util/delay.h"
#include "pwm.h"
#include "servo_driver.h"
#include "interrupt.h"

#include "ir.h"

#include "motor_driver.h"
#include "encoder.h"
#include "PID.h"
#include "can_definitions.h"
#include "solenoid.h"

/*
 * Main should listen to message from node 1 if it is gonna start the game or not.
 */

int main(void){
    USART_Init ( MYUBRR );
    set_bit(MCUCR,SRE);
    /*interrupt_init();
    USART_printf("Starting \n");
    interrupt_init();
    can_init(1);
    motor_init();
    encoder_init();
    PID_timer_init();
    PID_init();*/
    solenoid_init();
    while(1){
        solenoid_shoot();
        USART_printf("Tings kjer!!\n");
        _delay_ms(5000);
    };




    /*can_message recieved_msg;
    while(1){
        PID_update();
    	PID_update_system();

        //USART_printf("Ting skjyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyer\n");
        _delay_ms(5000);
    }*/

    /*
    ir_init();
    int i = 0;
    while(1){
      _delay_ms(2000);
      uint8_t val = adc_get_value();
      USART_printf("value = %d \n",val);
      USART_printf("%d",i);
      i++;
    }
    */


    //mcp_reset();
    /*while(1){
        set_bit(PORTB,SS);
        _delay_ms(1000);
        clear_bit(PORTB,SS);
        _delay_ms(1000);
        //mcp_reset();

        _delay_ms  interrupt_init();(2000);
        mcp_write(0x03, 0xD0);
        uint8_t ret = mcp_read(0x03);
        USART_printf("%x\n",ret);
    }

  */

  /*
  interrupt_init();

  can_init(1);
  pwm_init();

  can_message msg;
  msg.id = 1;
  msg.length = 3;
  msg.data[0] = 7;
  msg.data[1] = 2;
  msg.data[2] = 0;
 messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consit of General Call code or the TWI slave address.
          messageBuf[1] = TWI_CMD_MASTER_WRITE;             // The first byte is used for commands.
          messageBuf[2] = myCounter;                        // The second byte is used for the data.
TWI_Start_Transceiver_With_Data( messageBuf, 3 );
  //pwm_init();
  can_message new_msg;
  //servo_set_angle(-100);
  int i = 0;
  int8_t vx =0;
  int8_t vy = 0;
  while(1){
    i++;
    //can_transmit(&msg);
    _delay_ms(2000);
    //msg.data[2] = i;
    can_recieve(&new_msg);
    USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    vx = (int8_t) new_msg.data[0];
    vy = (int8_t) new_msg.data[1];
    USART_printf(", %d , %d \n",vx,vy );
    servo_set_angle(vx);
    USART_printf("ting skjer\n");
}


  //Test joystick signal
  */

}
