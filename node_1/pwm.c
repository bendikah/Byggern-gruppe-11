#include "pwm.h"
#include "global_defines.h"
#include <avr/io.h>

void pwm_init(void){

    //enable OC1A at PINB5 as output pin
#warning check which pin to use
    set_bit(DDRB,PINB5);
    //set fast PWM mode 14 - note icr1 becomes top mode
    set_bit(TCCR1A,WGM11);
    clear_bit(TCCR1A,WGM10);
    set_bit(TCCR1B,WGM12);
    set_bit(TCCR1B,WGM13);

    //set non-inverting mode meaning that OCnA is set to zero when TCNTn = OCRnX
    set_bit(TCCR1A, COM1A1);
    clear_bit(TCCR1A,COM1A0);

    //set prescale mode 64
    clear_bit(TCCR1B,CS12);
    set_bit(TCCR1B,CS11);
    set_bit(TCCR1B,CS10);

    //set top mode
    ICR1 = 5000;
    //set init pwm duty cycle. This is what is compared with TCNT counter.
    OCR1A = 375;


}

/*
 * If one would like to implement pwm_set_duty_cycle one has to take into acount that ICR1 can change and
 * is not necesseraly 5000.
 */
/*
void pwm_set_duty_cycle(float duty){ //make it easy to give in angle or whatever we want to use for changing.
    if (duty >= 0 || duty <= 100){
    OCR1A =(int) (duty *50);
    }
    else{
        OCR1A = 0;
    }
}*/

void pwm_set_frequency(int frequency){
    int top = 250000/frequency; //top is how many ticks TCNT gets per second
    ICR1 = top;
    OCR1A = top/2; //gives dutycycle of 50%
}