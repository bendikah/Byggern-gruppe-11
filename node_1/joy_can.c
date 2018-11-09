#include "breadboard_input.h"
#include "can_messages.h"
#include "can.h"
#include "joy_can.h"
#include "uart.h"
#include <stdint.h>

void joy_send_pos(void){
    struct Joystick_positions joy_pos = joystick_read_positions();
    //uint8_t value_x = joy_pos.x;
    //uint8_t value_y = joy_pos.y;
    //USART_printf("value x = %d value y = %d \n",value_x,value_y);
    msg_joy_positions.data[0] = joy_pos.x;
    msg_joy_positions.data[1] = joy_pos.y;
    msg_joy_positions.data[2] = joystick_read_button();
    msg_joy_positions.data[3] = slider_read_left();
    msg_joy_positions.data[4] = slider_read_right();
    USART_printf("Slider = %d\n", msg_joy_positions.data[4]);
    can_transmit(&msg_joy_positions);
}
