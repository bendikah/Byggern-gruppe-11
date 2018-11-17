#include <stdint.h>
#include "PID.h"
#include "encoder.h"
#include "motor_driver.h"
#include <avr/io.h>
#include "global_defines.h"
#include "uart.h"
#include <avr/interrupt.h>
#include "can_handler.h"
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

int16_t position;

uint8_t pid_interrupt_active;

void PID_init(){
	USART_printf("-------------------START---------\n");
	position = 0;
	reference = 0;
	kp = 1;
	ki = 250;
	kd = 1000;
	dt = 50;
	prevError = 0;
	integral = 0;
	control_input = 0;
}

void PID_print(){
	USART_printf("error = %d \n",error);
	USART_printf("control_input = %d \n", control_input);
	USART_printf("reference = %d \n",reference);
	USART_printf("position = %d \n",position);
	USART_printf("derivative = %d \n", derivative/kd);
	USART_printf("\n");
}

void PID_update(){
	PID_can_handler();
	error = reference - position;
	integral += error/ dt;
	derivative = (error - prevError) * dt;
	prevError = error;

	//USART_printf("error = %d \n",error);

	control_input = error/kp+ derivative/kd;
	//USART_printf("control_input = %d \n", control_input);
	PID_update_system();
}

void PID_update_system(){
	if(control_input > 0){
		motor_set_direction(0);
	}
	else if(control_input <= 0){
		motor_set_direction(1);
	}

	if(abs(control_input) > 90){
		motor_set_speed(90);
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
  ICR3 = 5000;
  pid_interrupt_active = 1;
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
void PID_stop(){
  //clear_bit(TIMSK3,OCIE3A);
  pid_interrupt_active = 0;
}

void PID_start(){
	pid_interrupt_active = 1;
}


ISR(TIMER3_COMPA_vect){
	//USART_printf("Interrupt virker \n");
	// Wake up the CPU!
	if (pid_interrupt_active == 1){
		PID_update();
	}
	//PID_update_system();

}


void PID_can_handler(){
	reference = 9180 - right_slider*4*9;
	position += encoder_read();

}
