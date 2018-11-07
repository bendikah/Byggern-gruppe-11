#include "can_messages.h"
#include "can_definitions.h"

can_message msg_joy_positions = {
  .id = JOY_POSITION_ID,
  .length = 5 // byte 0 = x-position, byte 1 = y-position, 2: joy_button, 3: left_slider, 4: right_slider
};

can_message msg_game_start = {
  .id = PINGPONG_GAME_START_ID,
  .lenght = 1,
  .data[0] = 0

};
