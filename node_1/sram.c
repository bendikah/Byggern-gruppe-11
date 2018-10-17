#include <avr/io.h>
#include "global_defines.h"
#include "sram.h"

void sram_initialize(void){
    set_bit(MCUCR,SRE);

}

void sram_write(uint8_t adress, uint8_t data){
    volatile char *ext_ram = (char *) 0x1800;

    ext_ram[adress] = data;
}

uint8_t sram_read(uint8_t adress){
    volatile char *ext_ram = (char *) 0x1800;
    return ext_ram[adress];
}
