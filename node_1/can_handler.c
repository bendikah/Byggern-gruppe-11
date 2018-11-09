#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "can_handler.h"
#include "can_definitions.h"
#include "can.h"

void can_handler_init(void){

  //set global interrupts
  SREG |= (1<<7);
  // Disable global interrupts
  cli();
  // Interrupt on falling edge PE0 we want for now only interrupt 0 which is set in MCUCR
  //EMCUCR &= ~(1<<ISC2);
  // Enable interrupt on INT0
  GICR |= (1<<INT0);
  // interrupt on falling edge (i dont know what EMCUCR thing does.. now i know :) )
  MCUCR &= ~(1<<ISC00);
  MCUCR |= (1<<ISC01);

  // Enable global interrupts
  sei();
}

ISR(INT0_vect){
  can_message recieved_msg;
    can_recieve(&recieved_msg);

    //USART_printf("Recieved something? \n");
    switch (recieved_msg.id) {

        default:
          break;

    }
}
