#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "can_handler.h"
#include "PID.h"
#include "can.h"
#include "can_definitions.h"

void can_handler_init(void){
  game_start = 0;
  //set global interrupts
  SREG |= (1<<7);
  // Disable global interrupts
  cli();
  // Interrupt on falling edge PE0 we want for now only interrupt 0 which is set in MCUCR
  //EMCUCR &= ~(1<<ISC2);
  // Enable interrupt on INT4  ?? INT2 som er koblet?
  EIMSK |= (1<<INT2);
  // interrupt on falling edge (i dont know what EMCUCR thing does.. now i know :) )
  EICRA &= ~(1<<ISC20);
  EICRA |= (1<<ISC21);

  // Enable global interrupts
  sei();
}


ISR(INT2_vect){
  can_message recieved_msg;
    can_recieve(&recieved_msg);
    USART_printf("Recieved something? \n");
    switch (recieved_msg.id) {
        case BREADBOARD_OUTPUT_ID:
            //USART_printf("recieved msg breadboard");
            joy_pos_x = recieved_msg.data[0];
            joy_pos_y = recieved_msg.data[1];
            joy_button = recieved_msg.data[2];
            left_slider = recieved_msg.data[3];
            right_slider = recieved_msg.data[4];
            //solenoid_can_handler(&recieved_msg);
        case PINGPONG_GAME_START_ID:
            game_start = 1;
            difficulty = recieved_msg.data[0];


    }
}
