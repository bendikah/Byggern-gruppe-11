#include "mcp_driver.h"
#include "spi.h"
#include "global_defines.h"
#include "util/delay.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "mcp_register.h"

#define MCP_READ 0x3
#define MCP_WRITE 0x2
#define MCP_RTS   0x80
#define MCP_READ_STATUS 0xA0
#define MCP_BIT_MODIFY 0x5
#define MCP_RESET 0xC0

#define SS 4
#define MOSI 5
#define SCK 7
#define PORTSPI PORTB


uint8_t mcp_read(uint8_t address){
  clear_bit(PORTSPI,SS);
  spi_transmit(0x03);
  spi_transmit(address);
  uint8_t read = spi_recieve();
  set_bit(PORTSPI, SS);
  return read;
}

void mcp_write(uint8_t address, uint8_t data){
  clear_bit(PORTSPI,SS);
  spi_transmit(MCP_WRITE);
  spi_transmit(address);
  spi_transmit(data);
  set_bit(PORTSPI,SS);
}

void mcp_request_to_send(uint8_t buffers){
  buffers &= 0b00000111;
  clear_bit(PORTSPI,SS);
  spi_transmit(MCP_RTS | buffers);
  set_bit(PORTSPI,SS);
}

uint8_t mcp_status(){
  clear_bit(PORTSPI,SS);
  spi_transmit(MCP_READ_STATUS);
  uint8_t status = spi_recieve();
  set_bit(PORTSPI,SS);
  return status;
}

void mcp_bit_modify(uint8_t address, uint8_t mask_byte, uint8_t data){
  clear_bit(PORTSPI,SS);
  spi_transmit(MCP_BIT_MODIFY);
  spi_transmit(address);
  spi_transmit(mask_byte);
  spi_transmit(data);
  set_bit(PORTSPI,SS);
}

void mcp_reset(){
  USART_printf("reset start \n");
  clear_bit(PORTSPI,SS);
  spi_transmit(MCP_RESET);
  set_bit(PORTSPI,SS);
  _delay_ms(10);
  uint8_t readval = mcp_read(MCP_CANSTAT);
  if ((readval & MODE_MASK) != MODE_CONFIG) {
    USART_printf("MCP NOT in config mode after reset %d \n", readval);
  }


}
