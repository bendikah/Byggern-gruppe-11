#include <avr/io.h>
#include "solenoid.h"
#include "global_defines.h"
#include "util/delay.h"


#define DDR_SOLENOID DDRF
#define PORT_SOLENOID PORTF
#define PIN_SOLENOID 1

void solenoid_init(){
    set_bit(DDR_SOLENOID, PIN_SOLENOID);
}

void solenoid_shoot(){
    set_bit(PORT_SOLENOID, PIN_SOLENOID);
    _delay_ms(100);
    clear_bit(PORT_SOLENOID, PIN_SOLENOID);
}
