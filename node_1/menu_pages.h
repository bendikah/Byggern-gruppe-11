
#ifndef MENU_PAGES_H
#define MENU_PAGES_H

#include <stdint.h>

#define MAX_MENU_CHILDREN   4
#define MAX_MENU_STRINGS    8
#define MAX_MENU_TITLE_SIZE 10

enum {MAIN = 0, PLAY, HIGH_SCORE, SETTINGS, CREDITS}; //used for index

struct menu_page {
    uint8_t index;
    char* label[MAX_MENU_TITLE_SIZE];
    menu_page* parent;
    menu_page* children[MAX_MENU_CHILDREN];
    uint8_t num_of_strings;
    const char* strings[MAX_MENU_STRINGS];

};

extern struct menu_page page_main;
extern struct menu_page page_play;
extern struct menu_page page_high_score;
extern struct menu_page page_settings;
extern struct menu_page page_credits;
#endif
