#ifndef CAN_HANDLER_H
#define CAN_HANDLER_H
void can_handler_init(void);

//Values from BREADBOARD_OUTPUT_ID
uint8_t joy_pos_x;
uint8_t joy_pos_y;
uint8_t joy_button;
uint8_t left_slider;
uint8_t right_slider;
uint8_t right_touch_button;

//values from PINGPONG_GAME_START_ID
uint8_t game_start;
uint8_t difficulty;


#endif
