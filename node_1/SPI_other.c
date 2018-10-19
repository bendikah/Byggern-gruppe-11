/*
 * SPI.c
 *
 * Created: 15.10.2017 17:02:24
 *  Author: thomasnl
 */

#include "SPI_other.h"

#include <avr/io.h>
#include "global_defines.h"
#include "util/delay.h"

void SPI_init()
{
	//Sets the Slave select, MOSI and SCK bits to output.
	DDRB |= (1<<DDB4)|(1<<DDB5)|(1<<DDB7);
	//Enable SPI, Master, set clock rate fck/16
	SPCR |= (1<<MSTR)|(1<<SPE)|(1<<SPR0);

}

void SPI_MasterTransmit(char cData)
{
	//Start transmission
	SPDR = cData;
	//Wait for the transmission to complete
	while (!(SPSR & (1<<SPIF)));
	//_delay_ms(200);

}

char SPI_MasterReceive()
{
	//Return the data register
	return SPDR;
}
