
#include "menu.h"
#include "oled.h"


enum {init = 0};


static int menu_branch;
static int menu_page;

#define NUM_OF_INIT_STRINGS		3
const char* page_init[] = {"Eivind\n", "Robert\n", "Bendik\n"};

//----------Local functions--------///
static void draw_page_init();

void menu_init(){
	menu_branch = 0;
	menu_page = init;
	menu_draw();
}

void menu_draw(void){
    oled_goto_line(0);
    oled_goto_column(0);
	switch(menu_page) {
        case init:
            draw_page_init();
            break;
        default:
            draw_page_init();
	}
}

void draw_page_init(){
	for (int i = 0; i < NUM_OF_INIT_STRINGS; i++){
		if (i == menu_branch){
			oled_printf("->");
		}
		oled_printf("%s", page_init[i]);
	}
}

void menu_increment_branch(){
	menu_branch++;
}

void menu_decrement_branch(){
	menu_branch--;
}

int get_menu_branch(){
	return menu_branch;
}