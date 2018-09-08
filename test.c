#include "global_defines.h"
#include "test.h"

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "util/delay.h"


void testThisShit(void){
	//DDRC = 0xFF;
	//PORTA = 0xFF;
	set_bit(DDRC,1);
	set_bit(DDRC,2);
	set_bit(DDRC,3);

	set_bit(PORTC,1);
	//set_bit(PORTC,2);
	//set_bit(PORTC,3);
	//_delay_ms(5000);
	//clear_bit(PORTE,1);

	//PORTA = 0x0;
	//_delay_ms(5000);
	//set_bit(PORTE,1);
}