
#ifndef IR_H
#define IR_H
#include "stdint.h"


void ir_init();
void ir_emit_light();
void ir_stop_emit_light();
void adc_init();
void adc_start();
void adc_stop();
uint8_t adc_get_value();
uint8_t ir_check_signal();
#endif
