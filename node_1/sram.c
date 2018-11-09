#include <avr/io.h>
#include "global_defines.h"
#include "sram.h"
#include "uart.h"

#include "util/delay.h"

void sram_initialize(void){
    set_bit(MCUCR,SRE);

}

void sram_write(uint16_t adress, uint8_t data){
    volatile char *ext_ram = (char *) 0x1800;
    ext_ram[adress] = data;
}

uint8_t sram_read(uint16_t adress){
    volatile char *ext_ram = (char *) 0x1800;
    uint8_t ret = ext_ram[adress];
    USART_printf(' '); //Needed this for sram_oled to work. Dont know why
    return ret;
}
