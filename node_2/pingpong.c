
#include "pingpong.c"
#include "motor_driver.h"
#include "servo_driver.h"
#include "solenoid.h"


void pingpong_start(){



    while(1){
        //if IR gets broken than brake the loop

        //recieve can message with ID joy_sliders...
        //if joybutton pushed -> solenoid_shoot();
        //use slider data to update reference of motor position
        //use joydata to set servo_angle
    }

    //when entering this you have lost the game

    //Send a can message to node 1 about the loss. (make oled print some stuff);

}