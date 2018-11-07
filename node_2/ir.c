
#include "ir.h"
#include "global_defines.h"
#include <stdint.h>
#include <avr/io.h>

#warning set a pin_number
#define IR_PIN
#define IR_PORT
#define IR_DPORT //direction port


int ir_flag; //bad name help
/*
 *How should we check for break in ir-light? Maybe an interupt? Or if we aren't doing anything else we can just have an
 * if setting and check. This has to be decided in the init function
 */

void ir_init(){
    //make it an output
    //set_bit(IR_DPORT, IR_PIN);
    ir_flag = 1;
    adc_init();
}

/*
void ir_emit_light(){
    set_bit(IR_PORT, IR_PIN);
}

void ir_stop_emit_light(){
    clear_bit(IR_PORT, IR_PIN);
}
*/

void adc_init(){
    set_bit(ADCSRA,ADEN); //enable adc
    set_bit(ADMUX,ADLAR); //leftshift to only represent inset_bit(ADCSRA, ADPS0);
    set_bit(ADCSRA, ADPS1);
    set_bit(ADCSRA, ADPS2);
    //set scaling for sampling 128?? This is only if we want to slow down the adc! but without it doesnt work.
    set_bit(ADCSRA, ADPS0);
    set_bit(ADCSRA, ADPS1);
    set_bit(ADCSRA, ADPS2);
    //set Voltage ref to VCC ?? do we need this ??
    //set_bit(ADMUX, REFS1);
    //clear_bit(ADMUX, REFS0);


    //test
    set_bit(ADMUX,REFS1);
    set_bit(ADMUX,REFS0);

    ADMUX &= ~(1 << MUX4) & ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
  }

void adc_start(){
  set_bit(ADCSRA,ADEN);
  set_bit(ADCSRA,ADSC);
}

void adc_stop(){
  clear_bit(ADCSRA,ADEN);
}

uint8_t adc_get_value(){
  set_bit(ADCSRA,ADSC);
  while(test_bit(ADCSRA,ADSC)){}
  return ADCH;
}

uint8_t ir_check_signal(){
    if (adc_get_value() > 230 && ir_flag == 1){
        ir_flag = 0;
        return 0;
    }
    else if(adc_get_value() < 220 && ir_flag == 0){
      ir_flag = 1;
      return 1;
    }
    return -1;
}
