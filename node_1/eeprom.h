

#ifndef EEPROM_H
#define EEPROM_H

/*-----------Define adresses for usage--------------*/
/* The 40 first adresses are users and their stats. Every four bytes is divided into 3 first as three chars (user)
    and the fourth is how many times they have played.
    From 40 there is 5*3 bytes which contains the 5 players with highest score.
*/
#define USER(n) 4*n
#define USER_STAT(n) 4*n+3
#define HIGH_SCORE(n) 4*(10+n)

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

unsigned char EEPROM_read(unsigned int uiAddress);



#endif
