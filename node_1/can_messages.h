#ifndef CAN_MESSAGES_H_
#define CAN_MESSAGES_H_

#include "can.h"

struct can_message msg_joy_positions = {
  .id = 0x333;
  .length = 3; // byte 0 = x-position, byte 1 = y-position
}

#endif /* CAN_MESSAGES_H_ */
