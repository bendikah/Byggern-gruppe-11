#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <stdio.h>
void motor_init();
void motor_set_speed(uint8_t speed);
void motor_set_direction(uint8_t dir);

#endif
