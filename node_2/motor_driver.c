#include "motor_driver.h"
#include "TWI_Master.h"
#include <stdio.h>
#include <avr/io.h>

#include "global_defines.h"
#include "uart.h"

//should have init for all

unsigned char messageBuf[3];
unsigned char TWI_targetSlaveAddress = 0x28;

void motor_init(void){
    //enable direction bit as output
    set_bit(DDRH,PH1);
    //enable motor bit
    set_bit(DDRH,PH4);
    set_bit(PORTH,PH4);


    TWI_Master_Initialise();
    //set motor speed 0


    motor_set_speed(0);
}

void motor_set_speed(uint8_t speed){
    messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consit of General Call code or the TWI slave address.
    messageBuf[1] = TWI_CMD_MASTER_WRITE;             // The first byte is used for commands.
    messageBuf[2] = speed;                        // The second byte is used for the data.
    TWI_Start_Transceiver_With_Data( messageBuf, 3 );

}

void motor_set_direction(uint8_t dir){
    if (dir > 0){
      set_bit(PORTH, PH1);
    }
    else if(dir == 0){
      clear_bit(PORTH,PH1);
    }
}
