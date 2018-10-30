

#ifndef load_and_save_H
#define load_and_save_H

/*-----------Define adresses for usage--------------*/
/* The 40 first adresses are users and their stats. Every four bytes is divided into 3 first as three chars (user)
    and the fourth is how many times they have played.
    From 40 there is 5*3 bytes which contains the 5 players with highest score.
*/


char* load_user(unsigned int number);

char* load_high_score(unsigned int number);

char* save_user(unsigned int number, char* user_name);

char* save_high_score(unsigned int number, char* user_name, uint8_t score);



#endif
