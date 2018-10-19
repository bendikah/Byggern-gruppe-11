/*
 * MCP2515.h
 *
 * Created: 16.10.2017 12:20:04
 *  Author: thomasnl
 */ 


#ifndef MCP2515_H_
#define MCP2515_H_
#include <stdint.h>

void MCP_init();

char MCP_Read(uint8_t address);

void MCP_Write(uint8_t address, uint8_t data);

void MCP_RequestToSend(uint8_t TXB);

char MCP_Read_Status();

void MCP_Bit_Modify(uint8_t address, uint8_t mask, uint8_t data);

void MCP_Reset();

uint8_t MCP_Get_ReceiveIntFlags();





#endif /* MCP2515_H_ */