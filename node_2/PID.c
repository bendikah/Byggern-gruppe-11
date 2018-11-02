#include <stdint.h>
#include "PID.h"
#include "encoder.h"
#include "motor_driver.h"
#include <avr/io.h>
#include "global_defines.h"
#include "uart.h"
#include <avr/interrupt.h>

uint16_t error;
int8_t integral;
int8_t derivative;
int8_t prevError;

uint16_t reference;
int8_t kp;
int8_t ki;
int8_t kd;
int8_t dt;

void PID_init(){
	reference = 0;
	kp = 10;
	ki = 0;
	kd = 0;
	dt = 0;
	prevError = 0;
	integral = 0;
}

void PID_update(){
	error = reference - encoder_read(); //get that encoder val;
	integral += error * dt;
	derivative = (error - prevError) / dt;
	prevError = error;
}

void update_system(){
	return;
	//com_set_u(kp*error + ki*integral + kd*derivative); SET MOTOR direction
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
  set_bit(TIMSK3,TOIE3);
	set_bit(TIMSK3,OCIE3A);
	sei();
  //enable interrupt on comparing counter 3 compare B
  //set_bit(TIMSK3,OCIE3B);
  //set top mode
  ICR3 = 5000;
	OCR3A =5000;

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
ISR(TIMER3_OVF_vect){
USART_printf("Interrupt virker \n");
// Wake up the CPU!
}
