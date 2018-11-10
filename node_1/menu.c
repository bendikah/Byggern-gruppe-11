
#include "menu.h"
#include "menu_pages.h"
#include "oled_sram.h"
#include "global_defines.h"
#include "util/delay.h"
#include <stdint.h>
#include "uart.h"







static int8_t menu_branch;
static struct menu_page* current_page;
static char current_user[3];



//----------Local functions--------///
static void draw_page_start();
static void draw_page_main();
static void draw_page_credits();
static void menu_print_welcome(char* user);

void menu_init(){
	menu_page_init();
	menu_branch = 0;
	current_page = &page_main;
	menu_draw();
}

void menu_draw(void){
    oled_sram_clear_screen();
	switch(current_page->index) {
        case MAIN:
            draw_page_main();
            break;
		case CREDITS:
			draw_page_credits();
			break;
		case START:
			draw_page_start();
			break;
        default:
            draw_page();
	}
}

void menu_increment_branch(){
	if (menu_branch >= current_page->num_of_strings - 1){
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

int8_t get_menu_branch(){
	return menu_branch;
}

void draw_page_start(){
	for (int i = 0; i < page_start.num_of_strings ; i++){
		if (page_start.strings[i] == "-"){
			continue;
		}
		if (i == menu_branch){
			//oled_printf("->");
			oled_sram_print("->");
		}
		//oled_printf("%s\n", page_main.strings[i]);
		oled_sram_print(page_start.strings[i]);
		oled_sram_print("\n");
	}
	oled_sram_update();
}

void draw_page(){
	for (int i = 0; i < current_page->num_of_strings ; i++){
		if (i == menu_branch){
			//oled_printf("->");
			oled_sram_print("->");
		}
		//oled_printf("%s\n", page_main.strings[i]);
		oled_sram_print(current_page->strings[i]);
		oled_sram_print("\n");
	}
	oled_sram_update();
}

void draw_page_main(){
	for (int i = 0; i < page_main.num_of_strings ; i++){
		if (i == menu_branch){
			//oled_printf("->");
			oled_sram_print("->");
		}
		//oled_printf("%s\n", page_main.strings[i]);
		oled_sram_print(page_main.strings[i]);
		oled_sram_print("\n");
	}
	oled_sram_update();
}

void draw_page_high_score(){
	for (int i = 0; i < page_high_score.num_of_strings; i++){
		//oled_printf("%i. %s\n", i, page_high_score.strings[i]);
#warning print out numbers
		//oled_sram_print()
		oled_sram_print(page_high_score.strings[i]);
		oled_sram_print("\n");
	}
	oled_sram_update();
}



void draw_page_credits(){
	for (int i = 7; i >= 0; i--){
			oled_sram_clear_screen();
		for (int j = 0; j < 8 - i; j++){
			oled_goto_line(i + j);
			oled_goto_column(0);
			//oled_printf(page_credits.strings[j]);
			oled_sram_print(page_credits.strings[j]);
		}
		oled_sram_update();
		_delay_ms(500);
	}
	for (int i = 1; i < page_credits.num_of_strings+1; i++){

		oled_sram_clear_screen();
		for (int j = 0; j < 8 ; j++){
			oled_goto_line(j);
			oled_goto_column(0);
			if (i + j >= page_credits.num_of_strings){
				break;
			}
			oled_sram_print(page_credits.strings[i + j]);
			//oled_printf(page_credits.strings[i+j]);
		}
		oled_sram_update();
		_delay_ms(500);
	}
	menu_previous_page();
}
/* To make it more starwars look-a-like we can have one line between the strings. And print the same
 * string row twice, but left and right shit to get the ends meeting.
 * Robert, your an amazing detective-slash-genius
 */
//char* current_user;

void menu_next_page(){
    if (current_page->children == NULL){
				return;
		}
		switch (current_page->index){
			case (START):
				oled_sram_clear_screen();
					//current_user = page_start.strings[menu_branch];
					menu_branch = 0;
					menu_print_welcome(current_user);
					_delay_ms(1500);
					break;
			case (MAIN):
					break;
		}
		current_page = current_page->children[menu_branch];
		menu_branch = 0;
		menu_draw();
}
void menu_previous_page(){
    if (current_page->parent == NULL) {
			return;
		}
    current_page = current_page->parent;
    menu_branch = 0;
    menu_draw();
}

void menu_print_welcome(char* user){
	oled_goto_line(3);
	oled_goto_column(10);
	oled_sram_print("Welcome ");
	#warning user is not a string
	oled_sram_print(user);
	oled_sram_update();
	_delay_ms(1000);
	oled_goto_line(4);
	oled_goto_column(10);
	oled_sram_print("FUN TIME!");
	oled_sram_update();
}
