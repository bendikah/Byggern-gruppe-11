#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "interrupt.h"

void interrupt_init(void){

  //set global interrupts
  SREG |= (1<<7);
  // Disable global interrupts
  cli();
  // Interrupt on falling edge PE0 we want for now only interrupt 0 which is set in MCUCR
  //EMCUCR &= ~(1<<ISC2);
  // Enable interrupt on INT4
  EIMSK |= (1<<INT2);
  // interrupt on falling edge (i dont know what EMCUCR thing does.. now i know :) )
  EICRA &= ~(1<<ISC20);
  EICRA |= (1<<ISC21);

  // Enable global interrupts
  sei();
}

ISR(INT2_vect){
USART_printf("Interrupt virker \n");
// Wake up the CPU!
}
