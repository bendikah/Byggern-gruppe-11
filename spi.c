#include "spi.h"
#include "global_defines.h"
#include <avr/io.h>

void spi_initialize(){

  //Set outputs - MISO already defined input
  set_bit(DDRB, SS);
  set_bit(DDRB, MOSI);
  set_bit(DDRB, SCK);

  set_bit(PORTSPI, SS);
  //set master Mode
  set_bit(SPCR,MSTR); //MSTR = bit4
  set_bit(SPCR,SPE); //SPE = 6
  set_bit(SPCR,SPR0); //SPR0 = 0 SCK frequenzy

}

char spi_transcieve(char data){
    SPDR = data;
    while(!(SPSR &(1<<SPIF))); //wait for transmit
    return SPDR;
}

void spi_transmit(uint8_t data){
  SPDR = data;
  while(!(SPSR &(1<<SPIF))); //wait for transmit
}

uint8_t spi_recieve(){
  spi_transmit('a'); //dummy send to receive newest value;
  return SPDR;
}



/*void spi_reset(){ //for later

}*/
