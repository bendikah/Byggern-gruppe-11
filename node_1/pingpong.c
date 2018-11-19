
#include "pingpong.h"
#include "can_messages.h"
#include "can.h"
#include "oled_sram.h"
#include "joy_can.h"

#include "global_defines.h"
#include "util/delay.h"
#include "can_handler.h"
#include "uart.h"

uint8_t pingpong_start(){
    oled_sram_clear_screen();
    oled_goto_line(2);
    oled_goto_column(10);
    oled_sram_print("Welcome to");
    oled_goto_line(3);
    oled_goto_column(10);
    oled_sram_print("PINGPONG!");
    oled_sram_update();
    can_transmit(&msg_game_start);
    _delay_ms(2000); //To give time to node 2 to check if ball in way or not
    while(ball_in_way){
        oled_goto_line(2);
        oled_goto_column(5);
        oled_sram_print("Please remove");
        oled_goto_line(3);
        oled_goto_column(10);
        oled_sram_print("the ball");
        oled_sram_update();
        _delay_ms(500);
        oled_sram_clear_screen();
        oled_sram_update();

         //blinking text!
        //USART_printf("Ball in the way\n");
        _delay_ms(500);
    }
    oled_sram_clear_screen();
    oled_sram_update();
    while (ball_in_way == 0){
        joy_send_pos();
        _delay_ms(15);
    }
    oled_sram_print("You got ");
    char streng[4];// = {0,0,0};
    sprintf(streng, "%d", pingpong_points);
    for (uint8_t n = 0; n < (uint8_t)ceil(log10(pingpong_points+1)); n++){
        oled_sram_put_char(streng[n]);
    }
    oled_sram_print(" points. \n");
    oled_sram_update();
    return pingpong_points;

}
