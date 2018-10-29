#include "menu_pages.h"
#include "eeprom.h"


extern struct menu_page page_start;

struct menu_page page_main = {
        .index = MAIN,
        .label[0] = "Main menu",
        .parent = NULL, //root oage
        .children[0] = &page_play,
        .children[1] = &page_high_score,
        .children[2] = &page_settings,
        .children[3] = &page_credits,
        .num_of_strings = 4,
        .strings[0] = "Play",
        .strings[1] = "High score",
        .strings[2] = "Settings",
        .strings[3] = "Credits"
};


struct menu_page page_play;
struct menu_page page_high_score = {
    .index = HIGH_SCORE,
    .label[0] = "High score",
    .parent = &page_main,
    .children[0] = NULL,
    .num_of_strings = 5
    //Does one have to read the highscoores in a init function?
};

struct menu_page page_settings;


struct menu_page page_credits = {
        .index = CREDITS,
        .label[0] = "Credits",
        .parent = &page_main,
        .children[0] = NULL,
        .num_of_strings = 8,
        .strings[0] = "Bernt Johan",
        .strings[1] = "Vegard",
        .strings[2] = "Kolbjørn",
        .strings[3] = "Waseem",
        .strings[4] = "Jo Arve",
        .strings[5] = "Bendik",
        .strings[6] = "Eivind",
        .strings[7] = "Robert"
};
