
#include "menu.h"
#include "menu_pages.h"
#include "oled_sram.h"
#include "global_defines.h"
#include "util/delay.h"
#include <stdint.h>
#include "uart.h"
#include "snake_game.h"
#include "breadboard_input.h"







static int8_t menu_branch;
static struct menu_page* current_page;
static char current_user[3];
static uint8_t user;



//----------Local functions--------///
static void draw_page_start();
static void draw_page_main();
static void draw_page_credits();
static void menu_print_welcome(uint8_t user);
static void draw_page_play();
static void draw_page_high_score();
static void draw_page_settings();
static void draw_page_pingpong();
static void draw_page_snake();
static void draw_page_snake_difficulty();

void menu_init(){
	menu_branch = 0;
	current_page = &page_main;
	menu_draw();
}


void add_user(uint8_t user_pos){
	oled_sram_clear_screen();
	_delay_ms(500);
	char letter = 'A';
	uint8_t i = 0;
	struct Joystick_positions joystick_positions;
	oled_goto_line(1);
	oled_sram_print("ADD USER");
	oled_goto_line(3);
	oled_goto_column(0);
	oled_sram_put_char('^');
	oled_goto_line(5);
	oled_goto_column(0);
	oled_sram_put_char('v');
	oled_goto_line(4);

	while(1){
		oled_goto_line(4);
		oled_goto_column(i*8);
		oled_sram_put_char(letter);
		joystick_positions = joystick_read_positions();
		if (joystick_positions.y >= 40){
			letter++;
		}
		else if (joystick_positions.y <= -40){
			letter--;
		}
		if (joystick_read_button()){
			current_user[i] = letter;
			letter = 'A';
			i++;
			if(i == 3){
				_delay_ms(500);
				oled_sram_update();
			break;}
			oled_goto_line(3);
			oled_goto_column((i-1)*8);
			oled_sram_put_char(' ');
			oled_sram_put_char('^');
			oled_goto_line(5);
			oled_goto_column((i-1)*8);
			oled_sram_put_char(' ');
			oled_sram_put_char('v');
			oled_goto_line(4);
			_delay_ms(500);
		}



		oled_sram_update();

		_delay_ms(100);
	}
	save_user(user_pos,current_user);
	user = user_pos;
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
		case PLAY:
			draw_page_play();
			break;
		case HIGH_SCORE:
			draw_page_high_score();
			break;
		case SNAKE:
			draw_page_snake();

        default:
				return;

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
	char temp_user[3];
	oled_sram_print("---CHOOSE USER---");
	oled_sram_put_char('\n');
	uint8_t i;
	for (i = 0; i < 2 ; i++){
		/*if (page_start.strings[i] == "-"){
			continue;
		}*/
		if (i == menu_branch){
			//oled_printf("->");
			oled_sram_print("->");
		}
		//oled_printf("%s\n", page_main.strings[i]);
		for (uint8_t j = 0; j < 3; j++){
			oled_sram_put_char(load_user(i,j));
		}
		//oled_sram_print(page_start.strings[i]);
		oled_sram_print("\n");
	}
	if (i == menu_branch){
		//oled_printf("->");
		oled_sram_print("->");
	}
	i++;
	oled_sram_print("GST");
	oled_sram_print("\n");
	if (i == menu_branch){
		//oled_printf("->");
		oled_sram_print("->");
	}
	oled_sram_print("ADD USER");
	oled_sram_update();

	return;
}

char* page_main_strings[5] = {"-----MAIN-----","PLAY","HIGH_SCORE","CREDITS","CHANGE USER"};

void draw_page_main(){

	for (int i = 0; i < 5; i++){
		if (i-1 == menu_branch){
			//oled_printf("->");
			oled_sram_print("->");
		}

		oled_sram_print(page_main_strings[i]);
		oled_sram_print("\n");
	}
	oled_sram_update();

}

void draw_page_high_score(){

	oled_sram_print("--HALL OF FAME-- \n");
	for(uint8_t i = 0; i < page_high_score.num_of_strings; i ++){
		for(uint8_t j = 0; j < 3; j ++){
			oled_sram_put_char(load_high_score_name(i,j));

		}
		oled_sram_print(" score: ");
		uint8_t temp_score = load_high_score_score(i);
		char streng[4];// = {0,0,0};
		sprintf(streng, "%d", temp_score);
		for (uint8_t n = 0; n < (uint8_t)ceil(log10(temp_score+1)); n++){
	    oled_sram_put_char(streng[n]);
	  }
		oled_sram_print("\n");
	}

	oled_sram_update();
	_delay_ms(5000);
	menu_branch = 0;
	current_page = &page_main;
	menu_draw();
}


char* page_credits_strings[7] = {"THANKS TO","BERNT JOHAN","VEGARD","KOLBJORN","BENDIK","EIVIND","ROBERT"};

void draw_page_credits_better(){
	for (uint8_t i = 0; i < 7*2;i ++){ //page Credits
			for(uint8_t k = 7; k > 0; k--){
				oled_goto_line(7);
				oled_sram_shift_whole_shit_one_bit();
					if (i%2 == 0){
				oled_sram_print_line(page_credits_strings[i/2],k);
					}

			oled_sram_update();



		}

	}
	for (uint8_t i = 0; i < 64; i++){
		oled_sram_shift_whole_shit_one_bit();
		oled_sram_update();

	}
}

void draw_page_credits(){
	for (uint8_t i = 0; i < 7*2;i ++){ //page Credits
			for(uint8_t k = 7; k > 0; k--){
				oled_goto_line(7);
				oled_sram_shift_whole_shit_one_bit();
					if (i%2 == 0){
				oled_sram_print_line(page_credits_strings[i/2],k);
					}

			oled_sram_update();
		}

	}
	for (uint8_t i = 0; i < 64; i++){
		oled_sram_shift_whole_shit_one_bit();
		oled_sram_update();

	}
	menu_previous_page();

}
char* page_play_strings[4] = {"-----PLAY-----","PINGPONG","SNAKE","BACK"};

static void draw_page_play(){
	for (int i = 0; i < 4; i++){
		if (i-1 == menu_branch){
			//oled_printf("->");
			oled_sram_print("->");
		}

		oled_sram_print(page_play_strings[i]);
		oled_sram_print("\n");
	}
	oled_sram_update();

	return;
}

static void draw_page_pingpong(){return;};

char* page_snake_strings[5] = {"----SNAKE-----","SINGLE PLAYER","MULTI PLAYER","SETTINGS", "BACK"};
static void draw_page_snake(){
	for (int i = 0; i < 5; i++){
		if (i-1 == menu_branch){
			//oled_printf("->");
			oled_sram_print("->");
		}

		oled_sram_print(page_snake_strings[i]);
		oled_sram_print("\n");
	}
	oled_sram_update();
	return;
}
static void draw_page_snake_difficulty(){return;}
/* To make it more starwars look-a-like we can have one line between the strings. And print the same
 * string row twice, but left and right shit to get the ends meeting.
 * Robert, your an amazing detective-slash-genius
 */
//char* current_user;

void menu_next_page(){
		switch (current_page->index){
			case (START):


					if (menu_branch == 3){
						add_user(0);
					}
					else {
						user = menu_branch;
					}
					menu_branch = 0;
					oled_sram_clear_screen();
					menu_print_welcome(user);
					_delay_ms(1500);
					break;
			case (MAIN):
					break;
			case (HIGH_SCORE):
					//draw_page_high_score();
					break;
			case (SNAKE):
					if (menu_branch == 0){
						int val = snake_run(0);
						//SAVE SCORE and print user scores
						oled_goto_line(4);
						oled_goto_column(8);
						oled_sram_print("SORRY YOU LOST");
						oled_sram_update();
						_delay_ms(4000);

					}
					else if (menu_branch == 1){
						snake_play_both();
					}
		}
		if (current_page->children[menu_branch] != NULL){
			current_page = current_page->children[menu_branch];
		}
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


void menu_print_welcome(uint8_t user){
	oled_goto_line(3);
	oled_goto_column(10);
	oled_sram_print("Welcome ");
	if (user < 2){
		for (int i = 0; i < 3; i++){
				oled_sram_put_char(load_user(user,i));
			}
		}
	oled_sram_update();
	_delay_ms(1000);
	oled_goto_line(4);
	oled_goto_column(10);
	oled_sram_print("FUN TIME!");
	oled_sram_update();
}
