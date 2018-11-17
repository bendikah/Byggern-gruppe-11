#include <avr/io.h>
#include <avr/interrupt.h>
#include "pingpong.h"
#include "motor_driver.h"
#include "servo_driver.h"
#include "solenoid.h"
#include "can.h"
#include "global_defines.h"
#include "uart.h"
#include "util/delay.h"
#include "PID.h"
#include "ir.h"
#include "can_handler.h"
#include "can_messages.h"

uint8_t number_of_points;
uint8_t pingpong_interrupt_active;

void pingpong_init(){
    ir_init();
    motor_init();
    //Go all the way to the right, startposition
    USART_printf("motor to the right\n");
    motor_set_speed(90);
    motor_set_direction(1);
    _delay_ms(3000);
    motor_set_speed(0);
    USART_printf("Motor is to the left\n");
    encoder_init();
    //reset the encoder for this position
    encoder_read();
    PID_init();

    PID_timer_init();
    PID_stop();

    pwm_init();
    solenoid_init();
    pingpong_timer_init();
    //set motor init solenoid init ?? up for discussion

}

uint8_t pingpong_start(){
    #warning also use difficulty
    while(ir_check_signal() == 0){
        can_transmit(&msg_remove_ball);
        _delay_ms(500);
    }
    can_transmit(&msg_game_starting);
    pingpong_timer_start();
    number_of_points = 0;
    PID_start();
    while(1){
        servo_set_angle((int8_t) joy_pos_x);
        //USART_printf("joy_pos_x = %d\n",joy_pos_x);
        int signal = ir_check_signal();
        if(signal == 0){
            break;
        }
        if (right_touch_button){
          solenoid_shoot();

        }
        //PID_print();
        _delay_ms(100);
    }

        //recieve can message with ID joy_sliders...
        /*can_extract_msg(&msg);*/
        //if joybutton pushed -> solenoid_shoot();

#warning Should this not be joy button in interrupt h?
        //if (msg.data[2] == 1){
          //  solenoid_shoot();
        //}
        //use slider data to update reference of motor position
        //PID_set_ref(msg.data[4]);
        //use joydata to set servo_angle
#warning thiss is wrong number since data is uint but the function needs an int from -100 to 100.
      //  servo_set_angle(msg.data[0]);

    //when entering this you have lost the game

    //Send a can message to node 1 about the loss. (make oled print some stuff);
    pingpong_timer_stop();
    PID_stop();
    motor_set_speed(0);
    return number_of_points;

}

void pingpong_timer_init(){
    cli();
    //set prescale mode
    //CS02 = 0 1 and 0 = 1 for 1024
    set_bit(TCCR4B,CS42);
    clear_bit(TCCR4B,CS41);
    set_bit(TCCR4B,CS40);

    clear_bit(TCCR4A,WGM41);
    clear_bit(TCCR4A,WGM40);
    set_bit(TCCR4B,WGM42);
    set_bit(TCCR4B,WGM43);

     //enable interrupt on counter 4
    set_bit(TIMSK4,OCIE4A);
    sei();
    ICR4 = 15625;
    pingpong_interrupt_active = 1;

}
void pingpong_timer_stop(){
  //clear_bit(TIMSK4,OCIE4A);
  pingpong_interrupt_active = 0;
}
void pingpong_timer_start(){
    //set_bit(TIMSK4,OCIE4A);
    pingpong_interrupt_active = 1;
}

ISR(TIMER4_COMPA_vect){
    if (pingpong_interrupt_active == 1){
        number_of_points ++;
    }

}
