
#include "pingpong.c"
#include "motor_driver.h"
#include "servo_driver.h"
#include "solenoid.h"
#include "can.h"
#include "PID.h"

void pingpong_start(){


    can_message msg;
    while(1){
        //if IR gets broken than brake the loop
        /*
         * if (ir_detect_brake()){brake;}
         */

        //recieve can message with ID joy_sliders...
        /*can_extract_msg(&msg);*/
        //if joybutton pushed -> solenoid_shoot();
        if (msg.data[2] == 1){
            solenoid_shoot();
        }
        //use slider data to update reference of motor position
        PID_set_ref(msg.data[4]);
        //use joydata to set servo_angle
#warning thiss is wrong number since data is uint but the function needs an int from -100 to 100.
        servo_set_angle(msg.data[0]);
    }

    //when entering this you have lost the game

    //Send a can message to node 1 about the loss. (make oled print some stuff);

}