
#include "load_and_save.h
#include "eeprom.h

/*-----------Define adresses for usage--------------*/
/* The 40 first adresses are users and their stats. Every four bytes is divided into 3 first as three chars (user)
    and the fourth is how many times they have played.
    From 40 there is 5*3 bytes which contains the 5 players with highest score.
*/
#define USER(n)         4*n
#define USER_STAT(n)    4*n+3
#define HIGH_SCORE(n)   4*(10+n)


char* load_user(unsigned int number){
    return [EEPROM_read(USER(number)),EEPROM_read(USER(number)+1), EEPROM_read(USER(number)+2),'\0'];
}

char* load_high_score(unsigned int number);

char* save_user(unsigned int number, char* user_name);

char* save_high_score(unsigned int number, char* user_name, uint8_t score);

