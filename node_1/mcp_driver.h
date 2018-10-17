#ifndef SPI_H
#define SPI_H
#include <avr/io.h>

uint8_t mcp_read(uint8_t address);
void mcp_write(uint8_t address, uint8_t data);
void mcp_request_to_send(uint8_t buffers);
uint8_t mcp_status();
void mcp_bit_modify(uint8_t address, uint8_t mask_byte, uint8_t data);
void mcp_reset();


#endif
