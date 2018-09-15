#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "test_sram.h"
#define F_CPU 4915200
#include "util/delay.h"

#include "test.h"

//#define FOSC 1968500// Clock Speed
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )


void main(void){
  //DDRA = 0xFF;
  USART_Init ( MYUBRR );
  //set_bit(MCUCR,SRE);
  //set_bit(MCUCR, ISC01);
  fdevopen(USART_Transmit, USART_Receive);

  //SRAM_test();
  testThisShit();
  //test_adc();
}
