#ifndef PID_H
#define PID_H

#include <stdint.h>

void PID_init();
void PID_update();
void PID_update_system();
void PID_timer_init();
void PID_can_handler(void);
void PID_set_ref(uint8_t ref);
void PID_stop();
void PID_start();

#endif
