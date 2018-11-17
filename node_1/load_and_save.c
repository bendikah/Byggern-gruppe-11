
#include "load_and_save.h"
#include "eeprom.h"

/*-----------Define adresses for usage--------------*/
/* The 40 first adresses are users and their stats. Every four bytes is divided into 3 first as three chars (user)
    and the fourth is how many times they have played.
    From 40 there is 5*3 bytes which contains the 5 players with highest score.
*/
#define NUM_OF_USERS    2
#define USER(n)         4*n
#define USER_STAT(n)    4*n+3
#define HIGH_SCORE(n)   4*(10+n)

#warning how to return a string?
char load_user(uint8_t number,uint8_t letter){
    //char* out = [EEPROM_read(USER(number)),EEPROM_read(USER(number)+1), EEPROM_read(USER(number)+2),'\0'];
    return EEPROM_read(USER(number) + letter);
}

char load_high_score_name(uint8_t number,uint8_t letter){
    //return (char[4]){EEPROM_read(HIGH_SCORE(number)), EEPROM_read(HIGH_SCORE(number)+1), EEPROM_read(HIGH_SCORE(number)+2), '\0'};
    return EEPROM_read(HIGH_SCORE(number)+letter);
}
uint8_t load_high_score_score(uint8_t number){
    return EEPROM_read(HIGH_SCORE(number)+3);
}

void save_user(uint8_t number, char* user_name){
    EEPROM_write(USER(number), user_name[0]);
    EEPROM_write(USER(number+1), user_name[1]);
    EEPROM_write(USER(number+2), user_name[2]);
}

void save_high_score(uint8_t number, char* user_name, uint8_t score){
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

void save_score(uint8_t user,uint8_t points){
    uint8_t placement = 5;
    char temp_user[3];
    uint8_t temp_score;
    for (uint8_t i = 0; i < 5; i++){
        if(load_high_score_score(i) < points){
            /*
            iterate from bottom to i;
            load user and points and save at placement below
            save this user and points at placement i.
            */
            for (uint8_t j = 4; j > i; j--){
                for (uint8_t k = 0; k < 3; k++){
                    temp_user[k] = load_high_score_name(j-1, k);
                }
                temp_score = load_high_score_score(j-1);
                save_high_score(j, temp_user, temp_score);
            }
            for (uint8_t k = 0; k < 3; k++){
                temp_user[k] = load_user(user, k);
            }
            save_high_score(i, temp_user, points);
            break;
        }
    }

}
