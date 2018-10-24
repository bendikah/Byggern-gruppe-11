/*
 * CAN.c
 *
 * Created: 16.10.2017 13:10:19
 *  Author: thomasnl
 */

#include "CAN_other.h"
#include "MCP2515.h"
#include "mcp2515_registers.h"
#include <avr/interrupt.h>
#include "global_defines.h"
#include "uart.h"


void CAN_init()
{
	USART_printf("we got in");
	MCP_Reset();
	USART_printf("Did we locate the error??");
	//Receive Buffer Operating mode bits - Turn mask/filters off; receive any message:
	MCP_Bit_Modify(MCP_RXB0CTRL,0b01100000,0b01100000);
	MCP_Bit_Modify(MCP_RXB1CTRL,0b01100000,0b01100000);

	//Interrupt Enable
	MCP_Bit_Modify(MCP_CANINTE, 0xFF, 0b00000011);
	USART_printf("we are half way");
	//Set NORMAL mode
	CAN_Set_Mode(MODE_NORMAL);

	//Enable interrupt on the INT1 pin on the atmega162
	set_bit(GICR,INT1);

	//Enable external interrupt on INT0 on falling edge
	set_bit(MCUCR,ISC11);
	USART_printf("Why we dont get past this??");

}

void CAN_Set_Mode(uint8_t mode)
{
	MCP_Bit_Modify(MCP_CANCTRL,MODE_MASK,mode);
}


void CAN_transmit(CAN_message_t message, uint8_t buffer)
{

	uint8_t offset = buffer*0x10;
	MCP_Write(0x31+offset, message.ID);
	MCP_Write(0x32+offset, message.ID);

	MCP_Bit_Modify(0x35+offset, 0b00001111, message.length);

	for(int i = 0; i < message.length; i++)
	{
		MCP_Write(0x36+offset + i, message.data[i]);
	}

	MCP_RequestToSend(buffer);
}


void CAN_receive(uint8_t buffer, CAN_message_t* message)
{
	if (((buffer == 0) && received_buffer0) || ((buffer == 1) && received_buffer1))
	{
		uint8_t offset = buffer*0x10;


		message->ID = MCP_Read(0x61 + offset);

		message->length = MCP_Read(0x65 + offset);

		for(int i = 0; i < 8; i++)
		{
			message->data[i] = MCP_Read((0x66 + i));
		}

		//Reread message ID to get correct ID
		message->ID = MCP_Read(0x61 + offset);

		//Turns off the interrupt flag corresponding to the buffer on the MCP and clears the received_buffer flag.
		switch(buffer)
		{
			case 0:
				MCP_Bit_Modify(MCP_CANINTF, 0b00000001, 0b00000000);
				CAN_clear_receive_buffer_0();
				break;

			case 1:
				MCP_Bit_Modify(MCP_CANINTF, 0b00000010, 0b00000000);
				CAN_clear_receive_buffer_1();
				break;

			default:
				//printf("\n\r !!CAN_receive on wrong buffer!! \n\r");
				break;
		}
	}

	else
	{
		//printf("!! CAN_receive: Interrupt Flags have not been set !!");
	}
}

void CAN_set_receive_buffer_0 ()
{
	received_buffer0 = 1;
}


void CAN_set_receive_buffer_1 ()
{
	received_buffer1 = 1;
}

int CAN_get_receive_buffer_1()
{
	return received_buffer1;
}

int CAN_get_receive_buffer_0()
{
	return received_buffer0;
}

void CAN_clear_receive_buffer_0()
{
	received_buffer0 = 0;
}

void CAN_clear_receive_buffer_1()
{
	received_buffer1 = 0;
}
