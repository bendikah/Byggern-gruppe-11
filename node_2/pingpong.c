#include <avr/io.h>
#include <avr/interrupt.h>
#include "pingpong.h"
#include "motor_driver.h"
#include "servo_driver.h"
#include "solenoid.h"
#include "can.h"
#include "global_defines.h"
#include "uart.h"
#include "util/delay.h"
#include "PID.h"
#include "ir.h"

uint8_t number_of_points;


void pingpong_init(){
    pingpong_timer_init();
    //set motor init solenoid init ?? up for discussion

}

void pingpong_start(){


    while(1){
      if(ir_check_signal() == 0){
      //send msg to node 1 remove ball
      USART_printf("REMOVE BALL YOU MORON \n");


    }
      if(ir_check_signal() == 1){
        USART_printf("ok now you can play \n");
        break;
      }
    }
    pingpong_timer_start();
    number_of_points = 0;
    while(1){
        //if IR gets broken than brake the loop
        /*
         * if (ir_detect_brake()){brake;}
         */
        if (ir_check_signal() == 0){

            break;
        }

        //recieve can message with ID joy_sliders...
        /*can_extract_msg(&msg);*/
        //if joybutton pushed -> solenoid_shoot();

#warning Should this not be joy button in interrupt h?
        //if (msg.data[2] == 1){
          //  solenoid_shoot();
        //}
        //use slider data to update reference of motor position
        //PID_set_ref(msg.data[4]);
        //use joydata to set servo_angle
#warning thiss is wrong number since data is uint but the function needs an int from -100 to 100.
      //  servo_set_angle(msg.data[0]);
    }

    //when entering this you have lost the game

    //Send a can message to node 1 about the loss. (make oled print some stuff);
    pingpong_timer_stop();

}

void pingpong_timer_init(){
    cli();
    //set prescale mode
    //CS02 = 0 1 and 0 = 1 for 1024
    set_bit(TCCR4B,CS42);
    clear_bit(TCCR4B,CS41);
    set_bit(TCCR4B,CS40);

    clear_bit(TCCR4A,WGM41);
    clear_bit(TCCR4A,WGM40);
    set_bit(TCCR4B,WGM42);
    set_bit(TCCR4B,WGM43);

     //enable interrupt on counter 4
    set_bit(TIMSK4,OCIE4A);
    sei();
    ICR4 = 15625;

}
void pingpong_timer_stop(){
  clear_bit(TIMSK4,OCIE4A);
}
void pingpong_timer_start(){
    set_bit(TIMSK4,OCIE4A);
}

ISR(TIMER4_COMPA_vect){
  USART_printf("working \n");
  number_of_points ++;

}
