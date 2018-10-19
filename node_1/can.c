#include "global_defines.h"
#include <avr/io.h>
#include "can.h"
#include "mcp_register.h"
#include "spi.h"
#include "mcp_driver.h"
#include <stdint.h>
#include "uart.h"

void can_init(uint8_t mode){
    spi_initialize();
    mcp_reset();
    /*
    switch (mode) {
      case 0:
      mcp_bit_modify(MCP_CANCTRL,0xE0,MODE_LOOPBACK);
      break;
      case 1:
      mcp_bit_modify(MCP_CANCTRL,0xE0,MODE_NORMAL);
    }
    */
    mcp_bit_modify(MCP_CANCTRL,0xE0,MODE_LOOPBACK); //set mode in canctrl register for now loopback only 3 first bits count see 10.4 mcp
    mcp_bit_modify(MCP_RXB0CTRL, 0x60, MCP_FILTER_OFF); //recieve all messages regardless of value see mcp 4.2.2
    mcp_bit_modify(MCP_RXB0CTRL, 0x04, MCP_ROLLOVER_OFF); //turn of overflow if 2 messages recieved
    mcp_bit_modify(MCP_CANINTE, 0xFF, MCP_RX_INT); //interrupt if message recieved on the __INT pin
}

void can_transmit(can_message* msg){

    while ((mcp_read(MCP_TXB0CTRL) & MCP_TXREQ)){} // when txreq bit is set transmit ready

    mcp_write(MCP_TXB0SIDH,msg -> id >> 3); //rightshift so we keep 5 msb
    mcp_write(MCP_TXB0SIDL,msg -> id << 5); //leftshift so we keep 3 lsb
    mcp_write(MCP_TXB0DLC,(msg->length) & 0x0F); // set message length




    //Set data bytes (max. 8 bytes)
		for (int i = 0; i < msg->length; i++) {
			mcp_write(MCP_TXB0D0 + i, msg->data[i]);
      }

    mcp_request_to_send(1);
}

can_message can_recieve(void){
    can_message msg;

    //if (mcp_read(MCP_CANINTF) & (MCP_RX0IF)){ // if something on the channel
        USART_printf("get some message");
        //Get message id
      msg.id = (mcp_read(MCP_RXB0SIDH) << 3) | (mcp_read(MCP_RXB0SIDL) >> 5);
		  msg.length = (mcp_read(MCP_RXB0DLC)) & (0x0F);
		  for (uint8_t i = 0; i < msg.length; i++){
			       msg.data[i] = mcp_read(MCP_RXB0D0 + i);
		}
    mcp_bit_modify(MCP_CANINTF, MCP_RX0IF, 0x00); //turn off interrupt of recieved

    //ELSE MESSAGE NOT RECIEVED RETURN SOME INDICATOR

    //}

    return msg;

}

/*
void can_printmsg(can_message msg){
	USART_printf("(can_msg_t){id:%x, len:%d, data:{",msg.id, msg.length);
	if(msg.length){
		printf("%x", msg.data[0]);
	}
	for(uint8_t i = 1; i < m.length; i++){
		printf(", %x", m.data[i]);
	}
	printf("}\n");
}

*/
