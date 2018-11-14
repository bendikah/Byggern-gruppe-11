

#ifndef MENU_H
#define MENU_H

#include <stdint.h>
void menu_init();
void menu_draw(void);
void menu_main();

void menu_increment_branch();

void menu_decrement_branch();

int8_t get_menu_branch();

void menu_next_page();
void menu_previous_page();
void add_user(uint8_t user_pos);
void draw_page_credits_better()
#endif
