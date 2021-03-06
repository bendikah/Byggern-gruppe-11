#include <stdint.h>
#include "PID.h"
#include "encoder.h"
#include "motor_driver.h"
#include <avr/io.h>
#include "global_defines.h"
#include "uart.h"
#include <avr/interrupt.h>
#include "interrupt.h"
#include <stdlib.h>

int16_t error;
int16_t integral;
int16_t derivative;
int16_t prevError;

int16_t reference;
int16_t kp;
int16_t ki;
int16_t kd;
int16_t dt;
int16_t control_input;

void PID_init(){
	reference = 0;
	kp = 2;
	ki = 0;
	kd = 0;
	dt = 0;
	prevError = 0;
	integral = 0;
	control_input = 0;
}

void PID_update(){
	PID_can_handler();
	error = reference - encoder_read(); //get that encoder val;
	integral += error * dt;
	derivative = (error - prevError) / dt;
	prevError = error;

	USART_printf("error = %d \n",error);

	control_input = kp*error;// + ki*integral + kd*derivative;
	USART_printf("control_input = %d \n", control_input);
	//PID_update_system();
}

void PID_update_system(){
	if(control_input > 0){
		motor_set_direction(0);
	}
	else if(control_input < 0){
		motor_set_direction(1);
	}
	if(abs(control_input) > 60){
		motor_set_speed(60);
		return;
	}

	motor_set_speed(abs(control_input));
}

void PID_timer_init(){

	cli();
  //set prescale mode 64
  clear_bit(TCCR3B,CS32);
  set_bit(TCCR3B,CS31);
  set_bit(TCCR3B,CS30);

  //Normal port operation, OC0A disconnected  set_bit(TCCR1A, COM1A1);
  //set_bit(TCCR3A, COM1A1);
  //clear_bit(TCCR3A,COM1A0);

  //set fast ctc pwm mode - note icr1 becomes top mode
  clear_bit(TCCR3A,WGM31);
  clear_bit(TCCR3A,WGM30);
  set_bit(TCCR3B,WGM32);
  set_bit(TCCR3B,WGM33);


  //enable interrupt on overflow counter 3
  	//set_bit(TIMSK3,TOIE3);
	set_bit(TIMSK3,OCIE3A);
	sei();
  //enable interrupt on comparing counter 3 compare B
  //set_bit(TIMSK3,OCIE3B);
  //set top mode
  ICR3 = 65000;
	//OCR3A =30000;

	/*
	// Disable global interrupts
	cli();

	// enable timer overflow interrupt for Timer2
	TIMSK2=(1<<TOIE2);

	// start timer2 with /1024 prescaler

	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);

	// Enable global interrupts
sei();
*/
}

/*
ISR(TIMER3_OVF_vect){
USART_printf("Interrupt virker \n");
// Wake up the CPU!
}

*/

void PID_set_ref(uint8_t ref){
	reference = ref*4*9-360;
#warning thiss is just some simple scaling. Should be better
}


ISR(TIMER3_COMPA_vect){
	//USART_printf("Interrupt virker \n");
	// Wake up the CPU!
	//PID_update();
	//PID_update_system();

}


void PID_can_handler(){
	reference = right_slider*4*9-360;
	USART_printf("reference = %d \n",reference);
	USART_printf("encoder = %d \n",encoder_read());


}
