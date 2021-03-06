#include "menu_pages.h"
#include "eeprom.h"
#include "load_and_save.h"


struct menu_page page_start = {
        .index = START,
        .parent = NULL,
        .children[0] = &page_main,
        .num_of_strings = 8
        //must initialize the strings in a init function
};

struct menu_page page_main = {
        .index = MAIN,
        .label[0] = "Main menu",
        .parent = &page_start, //root oage
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


struct menu_page page_play = {
    .index = PLAY,
    .label[0] = "Play"
};
struct menu_page page_high_score = {
    .index = HIGH_SCORE,
    .label[0] = "High score",
    .parent = &page_main,
    .children[0] = NULL,
    .num_of_strings = 5
    //Does one have to read the highscoores in a init function?
};

struct menu_page page_settings = {
    .index = SETTINGS
};


struct menu_page page_credits = {
        .index = CREDITS,
        .label[0] = "Credits",
        .parent = &page_main,
        .children[0] = NULL,
        .num_of_strings = 8,
        .strings[0] = "Bernt Johan",
        .strings[1] = "Vegard",
        .strings[2] = "Kolbjorn",
        .strings[3] = "Waseem",
        .strings[4] = "Jo Arve",
        .strings[5] = "Bendik",
        .strings[6] = "Eivind",
        .strings[7] = "Robert"
};

void menu_page_init(){
    // Load users
    for (int i = 0; i < page_start.num_of_strings - 2; i++){
        page_start.strings[i] = load_user(i);
    }
    page_start.strings[page_start.num_of_strings-2] = "GST";
    page_start.strings[page_start.num_of_strings-1] = "Add user";

    // Load high scores
    for (int i = 0; i < page_high_score.num_of_strings; i++){
        page_high_score.strings[i] = load_high_score_name(i);
#warning also load score. How to do score into a string?
    }
};
