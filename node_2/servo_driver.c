#include "servo_driver.h"
#include "global_defines.h"
#include <avr/io.h>
#include "pwm.h"

void servo_set_angle(int pos_x){



    float pwm_duty = 7.5+(float)pos_x*3/100;

    if(pwm_duty >= 4.5 && pwm_duty <= 10.5 ){
        pwm_set_duty_cycle(pwm_duty);
    }
}
