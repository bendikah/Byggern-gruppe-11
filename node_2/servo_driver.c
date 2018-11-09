#include "servo_driver.h"
#include "global_defines.h"
#include <avr/io.h>
#include "pwm.h"
#include "uart.h"
#include <stdint.h>

void servo_set_angle(int8_t pos_x){



    float pwm_duty = 7.5+(float)pos_x*3/100;

    if(pwm_duty >= 4.5 && pwm_duty <= 10.5 ){
        //USART_printf("pwm set duty cycle \n");
        pwm_set_duty_cycle(pwm_duty);
    }
}
