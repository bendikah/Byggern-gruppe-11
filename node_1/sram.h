#ifndef SRAM_H
#define SRAM_H

void sram_initialize(void);
void sram_write(uint8_t adress, uint8_t data);
uint8_t sram_read(uint8_t adress);


#endif
