#include "menu_pages.h"


extern struct menu_page page_main = {
        .index = MAIN,
        .label = "Main menu",
        .parent = NULL, //root oage
        .children[] = {&page_play, &page_high_score, &page_settings &page_credits},
        .num_of_strings = 4,
        .strings[] =  {"Play", "High score", "Settings", "Credits"}

};

extern struct menu_page page_play;
extern struct menu_page page_high_score;
extern struct menu_page page_settings;

extern struct menu_page page_credits = {
        .index = CREDITS,
        .label = "Credits",
        .parent = &page_main,
        .children = NULL,
        .num_of_strings = 8,
        .strings[] = {"Bernt Johan", "Vegard", "Kolbjørn", "Waseem", "Jo Arve", "Bendik", "Eivind", "Robert"}
};