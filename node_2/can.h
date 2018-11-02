#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>


union Can_data_t {
  uint8_t   u8[8];
  int8_t    i8[8];
};

typedef struct{
  int8_t id;
  uint8_t length;
  uint8_t data[8]; //8 bytes space in transmit registers of mcp
} can_message;

void can_init(uint8_t mode);
void can_transmit(can_message *msg);
void can_recieve(can_message* msg);


#endif /* CAN_H_ */
