#include "breadboard_input.h"
#include "can_message.h"
#include "can.h"
#include "joy_can.h"

void joy_send_pos(void){
    struct Joystick_positions joy_pos = joystick_read_positions();
    msg_joy_positions.data[0] = joy_pos.x;
    msg_joy_positions.data[1] = joy_pos.y;
    msg_joy_positions.data[2] = joystick_read_button();
    can_transmit(&msg_joy_positions);
}
