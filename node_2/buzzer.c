
#include "buzzer.h"
#include "global_defines.h"
#include <avr/io.h>
#include "util/delay.h"

void buzzer_init(){


    //enable OC1A at PINB5 as output pin
    //#warning wrong pin
    set_bit(DDRL,PIN3);
    //set fast PWM mode 14 - note icr1 becomes top mode
    set_bit(TCCR5A,WGM51);
    clear_bit(TCCR5A,WGM50);
    set_bit(TCCR5B,WGM52);
    set_bit(TCCR5B,WGM53);

    //set non-inverting mode meaning that OCnA is set to zero when TCNTn = OCRnX
    set_bit(TCCR5A, COM5A1);
    clear_bit(TCCR5A,COM5A0);

    //set prescale mode 64
    clear_bit(TCCR5B,CS52);
    set_bit(TCCR5B,CS51);
    set_bit(TCCR5B,CS50);

    //set top mode
    ICR5 = 500;
    //set init pwm duty cycle
    OCR5A = 250;


}
//250000 comes from clck cycle
void buzzer_set_tone(uint8_t tone, uint16_t duration){
    if (tone == 0){
        OCR5A = 0;
    }
    else {
        int top = 250000/tone; //top is how many ticks TCNT gets before restarting
        ICR5 = top;
        OCR5A = top/20; //gives dutycycle of 50%
    }
    while(duration--){
        _delay_ms(0.8);
    }
    OCR5A = 0;
}
