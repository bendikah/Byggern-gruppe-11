
#include "menu.h"
#include "oled.h"
#include "global_defines.h"
#include "util/delay.h"


enum {init = 0, credits};


static int menu_branch;
static int menu_page;

#define NUM_OF_INIT_STRINGS		4
const char* page_init[] = {"Play", "High score", "Settings", "Credits"};
#define NUM_OF_CREDIT_STRINGS	8
const char* page_credits[] = {"Bernt Johan", "Vegard", "Kolbjørn", "Waseem", "Jo Arve", "Bendik", "Eivind", "Robert"};

//----------Local functions--------///
static void draw_page_init();
static void draw_page_credits();

void menu_init(){
	menu_branch = 0;
	menu_page = init;
	menu_draw();
}

void menu_draw(void){
    oled_clear_screen();
	switch(menu_page) {
        case init:
            draw_page_init();
            break;
		case credits:
			draw_page_credits();
			break;
        default:
            draw_page_init();
	}
}

void menu_increment_branch(){
	if (menu_branch >= NUM_OF_INIT_STRINGS - 1){
		return;
	}
	menu_branch++;
	menu_draw();
}

void menu_decrement_branch(){
	if (menu_branch <= 0){
		return;
	}
	menu_branch--;
	menu_draw();
}

int get_menu_branch(){
	return menu_branch;
}

void draw_page_init(){
	for (int i = 0; i < NUM_OF_INIT_STRINGS; i++){
		if (i == menu_branch){
			oled_printf("->");
		}
		oled_printf("%s\n", page_init[i]);
	}
}

void draw_page_credits(){
	for (int i = 7; i >= 0; i--){
		for (int j = 0; j < 8 - i; j++){
			oled_goto_line(i + j);
			oled_sram_print(page_credits[j]);
		}
		oled_sram_update();
		_delay_ms(500);
	}
	for (int i = 1; i < NUM_OF_CREDIT_STRINGS; i++){
		for (int j = 0; j < 8 ; j++){
			oled_goto_line(j);
			if (i + j >= NUM_OF_CREDIT_STRINGS){
				break;
			}
			oled_sram_print(page_credits[i + j]);
		}
		oled_sram_update();
		_delay_ms(500);
	}

}