/*
 * MCP2515.c
 *
 * Created: 16.10.2017 12:19:44
 *  Author: thomasnl
 */


#include "MCP2515.h"
#include <avr/io.h>
#include "global_defines.h"
#include "mcp2515_registers.h"
#include "SPI_other.h"
#include "uart.h"

#define SPI_CS PB4

void MCP_init()
{
	//Set the SPI_CS PIN to output
	set_bit(DDRB,SPI_CS);
}

char MCP_Read(uint8_t address)
{
	//Select the slave
	clear_bit(PORTB,SPI_CS);
	//Tell the MCP we are going to read
	SPI_MasterTransmit(MCP_READ);
	//Send the address we are going to read from
	SPI_MasterTransmit(address);
	//Send a arbitrary byte to the slave.
	SPI_MasterTransmit('a');
	//Deselect the slave
	set_bit(PORTB,SPI_CS);

	//Return the value that has been shifted SPI-register
	return SPI_MasterReceive();
}

void MCP_Write(uint8_t address, uint8_t data)
{
	//Select the slave
	clear_bit(PORTB,SPI_CS);
	//Tell the MCP we are going to write
	SPI_MasterTransmit(MCP_WRITE);
	//Send the address we are going to write to
	SPI_MasterTransmit(address);
	//Send the data thats going to be written
	SPI_MasterTransmit(data);
	//Deselect the slavemcp_read
	set_bit(PORTB,SPI_CS);
}


void MCP_RequestToSend(uint8_t TXB)
{
	//Select slave
	clear_bit(PORTB,SPI_CS);

	switch(TXB)
	{
		case 0:
			SPI_MasterTransmit(MCP_RTS_TX0);
			break;
		case 1:
			SPI_MasterTransmit(MCP_RTS_TX1);
			break;
		case 2:
			SPI_MasterTransmit(MCP_RTS_TX2);
			break;

		default:
			SPI_MasterTransmit(0x80);
			break;
	}

	//Deselect slave
	set_bit(PORTB,SPI_CS);
}

char MCP_Read_Status()
{
	clear_bit(PORTB,SPI_CS);


	SPI_MasterTransmit(MCP_READ_STATUS);
	SPI_MasterTransmit('a');
	return SPI_MasterReceive();


	set_bit(PORTB,SPI_CS);
}

void MCP_Bit_Modify(uint8_t address, uint8_t mask, uint8_t data)
{
	clear_bit(PORTB,SPI_CS);


	SPI_MasterTransmit(MCP_BITMOD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(mask);
	SPI_MasterTransmit(data);


	set_bit(PORTB,SPI_CS);
}

void MCP_Reset()

{
	USART_printf("1");
	clear_bit(PORTB,SPI_CS);
USART_printf("2");
	SPI_MasterTransmit(MCP_RESET);
USART_printf("3");
	set_bit(PORTB,SPI_CS);
}

uint8_t MCP_Get_ReceiveIntFlags()
{
	return MCP_Read(MCP_CANINTF);
}
