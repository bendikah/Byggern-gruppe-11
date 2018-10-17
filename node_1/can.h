#ifndef CAN_H_
#define CAN_H_



typedef struct{
  int8_t id;
  uint8_t length;
  uint8_t data[8] //8 bytes space in transmit registers of mcp 
  } can_message;

void can_init(uint8_t mode);
void can_transmit(can_message *msg);
can_message can_recieve(void);


#endif /* CAN_H_ */
