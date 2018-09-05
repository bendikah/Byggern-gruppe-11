#include <avr/io.h>
#include "uart.h"
#include <stdio.h>
//typedef struct __file FILE

void USART_Init(unsigned int ubrr )
{
/*
Set baud rate
 */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/*
Enable receiver and transmitter
 */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/*
Set frame format: 8data, 2stop bit
 */
UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}



void USART_Transmit(char data ){
/*
Wait for empty transmit buffer
 */
 if (data == '\n'){
   USART_Transmit('\r');
 }
 while ( !( UCSR0A & (1<<UDRE0)) );
/*
Put data into buffer, sends the data
 */
 UDR0 = data;
}


unsigned int USART_Receive(void){
  //unsigned char status, resh, resl;
  /*
  Wait for data to be received
  */
  while ( !(UCSR0A & (1<<RXC0)) );
  /*
  Get status and 9th bit, then data
  */
  /*
  from buffer
  */
  /*status = UCSRA;
  resh = UCSRB;
  resl = UDR;*/
  /*
  If error, return -1
  */
  /*if( status & (1<<FE)|(1<<DOR)|(1<<UPE) )
    return -1;*/
  /*
  Filter the 9th bit, then return
  */
  /*resh = (resh >> 1) & 0x01;
  return((resh << 8) | resl);*/
  return UDR0;
}


//int fdevopen(void (*USART_Transmit), unsigned char (*USART_Receive));
