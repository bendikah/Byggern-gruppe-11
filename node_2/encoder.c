/*
Set !OE low to enable output of encoder
•  Set SEL low to get high byte
•  Wait about 20 microseconds
•  Read MSB
•  Set SEL high to get low byte
•  Wait about 20 microseconds
•  Read LSB
•  Toggle !RST to reset encoder
•  Set !OE high to disable output of encoder
•  Process received data....
*/

#include "global_defines.h"
#include <avr/io.h>
#include <stdint.h>
#include "uart.h"
#include "util/delay.h"

#define NOT_RST PH6
#define SEL PH3
#define NOT_OE PH5


void encoder_init(){
      //enable SEL, OE, RST
      set_bit(DDRH,SEL);
      set_bit(DDRH,NOT_OE);
      set_bit(DDRH,NOT_RST);
      //set RST
      set_bit(PORTH,NOT_RST);
}
//val += encoder_read()
int16_t encoder_read(){
    int16_t encoder_val;

    //Set !OE low to enable output of encoder
    clear_bit(PORTH,NOT_OE);
    //read MSB
    clear_bit(PORTH,SEL);
    _delay_us(20);
    encoder_val = (PINK << 8);
    set_bit(PORTH,SEL);
    _delay_us(20);
    encoder_val = encoder_val | PINK;

    //toggle RST
    clear_bit(PORTH,NOT_RST);
    _delay_us(20);
    set_bit(PORTH,NOT_RST);
    set_bit(PORTH,NOT_OE);

    return encoder_val;
}
