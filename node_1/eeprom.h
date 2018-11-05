

#ifndef EEPROM_H
#define EEPROM_H


void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

unsigned char EEPROM_read(unsigned int uiAddress);


#endif
