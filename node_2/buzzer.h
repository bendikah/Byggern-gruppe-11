
#ifndef BUZZER_H
#define BUZZER_H
#include <stdint.h>

void buzzer_init();
void buzzer_set_tone(uint8_t tone, uint16_t duration);

#endif
