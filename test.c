#include "global_defines.h"
#include "test.h"
#include "breadboard_input.h"

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "util/delay.h"


void testThisShit(void){
	//DDRC = 0xFF;
	//PORTC = 0;
	/*set_bit(DDRC,1);
	set_bit(DDRC,2);
	set_bit(DDRC,3);

	set_bit(PORTC,1);*/
	//set_bit(PORTC,2);
	//set_bit(PORTC,3);
	//_delay_ms(5000);
	//clear_bit(PORTC,1);

	//PORTA = 0x0;
	//_delay_ms(5000);
	//set_bit(PORTE,1);

	volatile char *ext_ram = (char *) 0x1400; // Start address for the SRAM
 	//uint16_t ext_ram_size= 0x400;
 	//uint16_t write_errors= 0;
 	//uint16_t retrieval_errors= 0;
 	printf("Starting ADC test...\n");
 	// rand() stores some internal state, so calling this function in a loop will
 	// yield different seeds each time (unless srand() is called before this function)
 	//uint16_t seed = rand();
 	// Write phase: Immediately check that the correct value was stored
 	//srand(seed);
 	/*for (uint16_t i = 0; i < ext_ram_size; i++) {
    //uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		printf("Output joy [%4d] = %02X \n",i,retreived_value);

    }*/
 	while(1){
	 	//for(int i = 0; i <= 8; i++){
 		ext_ram[0] = 7;
 		_delay_ms(100);
		    uint8_t retreived_value = ext_ram[0];
			printf("Output joy [x] = %02X \n",retreived_value);
			_delay_ms(300);
		//}
	}
}

void test_adc(void){
	while(1){
	uint8_t read_number_x = joystick_read_x();
	uint8_t read_number_y = joystick_read_y();
	uint8_t l_slider = slider_read_left();
	uint8_t r_slider = slider_read_right();
	printf("this is the values x = %02X y = %02X L_slider = %02X and R_slider = %02X \n",read_number_x,read_number_y,l_slider,r_slider);
	}
}
