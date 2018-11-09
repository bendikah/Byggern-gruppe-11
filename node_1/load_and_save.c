
#include "load_and_save.h"
#include "eeprom.h"

/*-----------Define adresses for usage--------------*/
/* The 40 first adresses are users and their stats. Every four bytes is divided into 3 first as three chars (user)
    and the fourth is how many times they have played.
    From 40 there is 5*3 bytes which contains the 5 players with highest score.
*/
#define NUM_OF_USERS    6
#define USER(n)         4*n
#define USER_STAT(n)    4*n+3
#define HIGH_SCORE(n)   4*(10+n)

#warning how to return a string?
char* load_user(unsigned int number){
    //char* out = [EEPROM_read(USER(number)),EEPROM_read(USER(number)+1), EEPROM_read(USER(number)+2),'\0'];
    return EEPROM_read(USER(number));
}

char* load_high_score_name(unsigned int number){
    return (char[4]){EEPROM_read(HIGH_SCORE(number)), EEPROM_read(HIGH_SCORE(number)+1), EEPROM_read(HIGH_SCORE(number)+2), '\0'};
    //return EEPROM_read(HIGH_SCORE(number));
}
uint8_t load_high_score_score(unsigned int number){
    return EEPROM_read(HIGH_SCORE(number)+3);
}

void save_user(unsigned int number, char* user_name){
    EEPROM_write(USER(number), user_name[0]);
    EEPROM_write(USER(number+1), user_name[1]);
    EEPROM_write(USER(number+2), user_name[2]);
}

void save_high_score(unsigned int number, char* user_name, uint8_t score){
    EEPROM_write(HIGH_SCORE(number), user_name[0]);
    EEPROM_write(HIGH_SCORE(number)+1, user_name[1]);
    EEPROM_write(HIGH_SCORE(number)+2, user_name[2]);
    EEPROM_write(HIGH_SCORE(number)+3, score);
}

void reboot(){
    for (int i = 0; i < NUM_OF_USERS; i++){
      save_user(i, "-");
    }
}
