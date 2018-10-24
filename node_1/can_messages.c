#include "can_messages.h"


can_message msg_joy_positions = {
  .id = 0x33,
  .length = 3 // byte 0 = x-position, byte 1 = y-position
};
