
#include "menu.h"
#include "menu_pages.h"
#include "oled.h"
#include "global_defines.h"
#include "util/delay.h"
#include <stdint.h>







static int menu_branch;
static struct menu_page* current_page;



//----------Local functions--------///
static void draw_page_main();
static void draw_page_credits();

void menu_init(){
	menu_branch = 0;
	current_page = &page_main;
	menu_draw();
}

void menu_draw(void){
    oled_clear_screen();
	switch(current_page->index) {
        case MAIN:
            draw_page_main();
            break;
		case CREDITS:
			draw_page_credits();
			break;
        default:
            draw_page_main();
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

int get_menu_branch(){
	return menu_branch;
}

void draw_page_main(){
	for (int i = 0; i < page_main.num_of_strings ; i++){
		if (i == menu_branch){
			oled_printf("->");
		}
		oled_printf("%s\n", page_main.strings[i]);
	}
}



void draw_page_credits(){
	/*for (int i = 7; i >= 0; i--){
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
	}*/

}/* To make it more starwars look-a-like we can have one line between the strings. And print the same
 * string row twice, but left and right shit to get the ends meeting.
 * Robert, your an amazing detective-slash-genius
 */

void menu_next_page(){
    if (current_page->children != NULL){
        current_page = current_page->children[menu_branch];
        menu_branch = 0;
    }
    return;
}
void menu_previous_page(){
    if (current_page->parent != NULL) {
        current_page = current_page->parent;
        menu_branch = 0;
    }
    return;
}
