

#ifndef LOAD_AND_SAVE_H
#define LOAD_AND_SAVE_H
#include <stdio.h>

/*
 * A user consists of three letters. They are saved in eeprom consentent(?) (etter hverandre).
 * After a user (three letters) it is saved a stat which shows how many times the player has played.
 * The highscores are saved in order of highest score to lowest score.
 * Each highscore consists of three letters, representing the user, and a score.
 */

void reboot();

char* load_user(unsigned int number);

char* load_high_score_name(unsigned int number);
uint8_t load_high_score_score(unsigned int number);

void save_user(unsigned int number, char* user_name);

void save_high_score(unsigned int number, char* user_name, uint8_t score);



#endif
