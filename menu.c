
#include "menu.h"
#include "oled.h"


enum {init = 0};

static int menu_branch;
static int menu_page;

//----------Local functions--------///
static void draw_init_menu();

void menu_init(){
	menu_branch = 0;
	menu_page = init;
	draw_init_menu();
}

void menu_draw(void){
	return;
}

void draw_init_menu(){
	oled_print("Eivind\n");
	oled_print("Robert\n");
	oled_print("Bendik\n");
	oled_print("Jonass\n");
	oled_print("5 Bokstaver\n");
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