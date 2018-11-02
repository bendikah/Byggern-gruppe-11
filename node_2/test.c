
#include "test.h"
#include "can.h"
#include "can_definitions.h"
#include "motor_driver.h"
#include "global_defines.h"
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "util/delay.h"
#include <stdlib.h>
#include "encoder.h"

#warning should probably be put somewhere else??
#define JOY_THRESHOLD   30

void test_motor_by_joystick(){
  interrupt_init();
  can_init(1);
  motor_init();

  can_message recieved_msg;
  int8_t vx =0;
  while(1){
    can_recieve(&recieved_msg);
    //USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    vx = (int8_t) recieved_msg.data[0];
    //vy = (int8_t) new_msg.data[1];
    USART_printf("vx = %d \n",vx);
    if (vx < 0-JOY_THRESHOLD){
      motor_set_direction(0);
    }
    else if (vx > JOY_THRESHOLD){
      motor_set_direction(1);
    }
    else{
      vx = 0;
    }
    motor_set_speed(abs(vx));
    _delay_ms(300);
  }
}

void test_encoder(){
  interrupt_init();
  can_init(1);
  motor_init();
  encoder_init();

  can_message recieved_msg;
  int8_t vx =0;
  while(1){
    can_recieve(&recieved_msg);
    //USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    vx = (int8_t) recieved_msg.data[0];
    //vy = (int8_t) new_msg.data[1];
    USART_printf("vx = %d \n",vx);
    if (vx < 0-JOY_THRESHOLD){
      motor_set_direction(0);
    }
    else if (vx > JOY_THRESHOLD){
      motor_set_direction(1);
    }
    else{
      vx = 0;
    }
    motor_set_speed(abs(vx));
    _delay_ms(1000);


    USART_printf("encoder val : %d",encoder_read());
  }

}
