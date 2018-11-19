
#include "adc.h"
#include "global_defines.h"
#include "util/delay.h"


volatile char *start_adc = (char *) 0x1400;

uint8_t adc_read(int channel){
	start_adc[0] = channel;
	return start_adc[0];
}

