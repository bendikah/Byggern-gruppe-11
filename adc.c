
#include "adc.h"
#include "global_defines.h"
#include "util/delay.h"


volatile char *start_adc = (char *) 0x1400;

uint8_t adc_read(int channel){
	start_adc[0] = channel;
 	_delay_ms(50); //do we need this?????????!!!!!!!!!!!!!!!111
	return start_adc[0];
}

