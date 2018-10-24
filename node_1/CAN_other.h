/*
 * CAN.h
 *
 * Created: 16.10.2017 13:10:07
 *  Author: thomasnl
 */ 


#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>
	

typedef struct  
{
	uint8_t ID;
	uint8_t length;
	int8_t data[8];
}CAN_message_t;


static uint8_t received_buffer0 = 0;
static uint8_t received_buffer1 = 0;


void CAN_set_receive_buffer_0();


void CAN_set_receive_buffer_1();


int CAN_get_receive_buffer_0();


int CAN_get_receive_buffer_1();


void CAN_clear_receive_buffer_0();


void CAN_clear_receive_buffer_1();


void CAN_init();


void CAN_Set_Mode(uint8_t mode);


void CAN_transmit(CAN_message_t message, uint8_t buffer);

//Takes in a buffer and an empty CAN_message, and puts what is in the buffer in the CAN_message. Caller must check if receive buffer flag is set on the buffer.
void CAN_receive(uint8_t buffer, CAN_message_t* message);



#endif /* CAN_H_ */