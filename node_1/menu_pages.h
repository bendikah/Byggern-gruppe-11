
#ifndef MENU_PAGES_H
#define MENU_PAGES_H

#include <stdint.h>
#if !defined(NULL)
    #define NULL ((void*)0)
#endif

#define MAX_MENU_CHILDREN   4
#define MAX_MENU_STRINGS    8
#define MAX_MENU_TITLE_SIZE 10

enum {START, MAIN, PLAY, HIGH_SCORE, SETTINGS, CREDITS}; //used for index

struct menu_page;

struct menu_page {
    uint8_t index;
    char* label[MAX_MENU_TITLE_SIZE];
    struct menu_page* parent;
    struct menu_page* children[MAX_MENU_CHILDREN];
    uint8_t num_of_strings;
    const char* strings[MAX_MENU_STRINGS];

};

void menu_page_init();

extern struct menu_page page_start;
extern struct menu_page page_main;
extern struct menu_page page_play;
extern struct menu_page page_high_score;
extern struct menu_page page_settings;
extern struct menu_page page_credits;
#endif
