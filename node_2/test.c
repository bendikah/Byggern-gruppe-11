
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
#include "can_handler.h"
#include "solenoid.h"
#include "ir.h"

#warning should probably be put somewhere else??
#define JOY_THRESHOLD   30

void test_motor_by_joystick(){
  //interrupt_init();
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
  can_handler_init();
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

void test_solenoid(){
  solenoid_init();
  while(1){
      solenoid_shoot();
      USART_printf("Tings kjer!!\n");
      _delay_ms(5000);
  }

}

void test_ir(){
  ir_init();
  int i = 0;
  while(1){
    _delay_ms(2000);
    int signal = ir_check_signal();
    if(signal == 0){
        USART_printf("You lost a life \n");
    }
    else if(signal == 1){
      USART_printf("new game starting \n");
    }
    USART_printf("counter %d \n",i);
    i++;
  }

}

void test_can(){

  can_init(1);

  can_message new_msg;
  can_message msg;
  msg.id = 1;
  msg.length = 3;
  msg.data[0] = 7;
  msg.data[1] = 2;
  msg.data[2] = 0;

  int i = 0;

  while(1){
    i++;
    can_transmit(&msg);
    _delay_ms(2000);
    msg.data[2] = i;
    can_recieve(&new_msg);
    USART_printf("(can_msg_t){id:%x, len:%d, data:{",new_msg.id, new_msg.length);
    for(int i = 0; i < new_msg.length; i++){
  		  USART_printf(", %x", new_msg.data[i]);
  	}
		USART_printf("\n");
}

}
