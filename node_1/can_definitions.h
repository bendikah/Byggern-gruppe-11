
#ifndef CAN_DEFINITIONS_H
#define CAN_DEFINITIONS_H


#define NODE1   0x10
#define NODE2   0x30

#define JOY_POSITION_ID   NODE1 | 0x00
//bytes are ordered like 0: joy.x, 1: joy.y, 2: joy_button, 3: sliders.left, 4:sliders.right

#define PINGPONG_GAME_START_ID NODE1 | 0x01

#define LOST_GAME_ID NODE2 | 0x00
#define REMOVE_BALL_ID NODE2 | 0x01
#define GAME_STARTING_ID NODE2 | 0x02


#endif
