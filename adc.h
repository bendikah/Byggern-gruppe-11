
#ifndef ADC_H
#define ADC_H

/*---------------ADC----------------*/
#define CHANNEL_1	4
#define CHANNEL_2	5
#define CHANNEL_3	6
#define CHANNEL_4	7
/*----------------------------------*/

#include <stdint.h>


uint8_t read_adc(int channel);


#endif
