#include "can_messages.h"
#include "can_definitions.h"

can_message msg_lost_game = {
  .id = LOST_GAME_ID,
  .length = 1 // byte 0 = x-position, byte 1 = y-position, 2: joy_button, 3: left_slider, 4: right_slider
};

can_message msg_remove_ball = {
    .id = REMOVE_BALL_ID,
    .length = 0
};

can_message msg_game_starting = {
    .id = GAME_STARTING_ID,
    .length = 0
};
