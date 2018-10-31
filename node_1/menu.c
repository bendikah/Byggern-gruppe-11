
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
const char* page_credits[] = {"Bernt Johan", "Vegard", "Kolbjorn", "Waseem", "Jo Arve", "Bendik", "Eivind", "Robert"};

//----------Local functions--------///
static void draw_page_init();
static void draw_page_credits();

void menu_init(){
	menu_branch = 0;
	menu_page = credits;
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
			oled_goto_column(0);
			oled_printf(page_credits[j]);
		}
		//oled_sram_update();
		_delay_ms(500);
		oled_clear_screen();
	}
	for (int i = 1; i < NUM_OF_CREDIT_STRINGS; i++){
		for (int j = 0; j < 8 ; j++){
			oled_goto_line(j);
			oled_goto_column(0);
			if (i + j >= NUM_OF_CREDIT_STRINGS){
				break;
			}
			oled_printf(page_credits[i + j]);
		}
		//oled_sram_update();
		_delay_ms(500);
		oled_clear_screen();
	}

}
/*
void draw_page_credits(){
	//for (int shiftbits = 7; shiftbits > 0; shiftbits--){
    for (int i = 7; i >= 0; i--){ //start line
				oled_clear_screen();
        for (int j = 0; j < 8 - i; j++){ //from startline to bottom
            oled_goto_line(j+i);

            //for (int shiftbits = 7; shiftbits > 0; shiftbits--){ //number of bits shifted
							oled_goto_column(0);
                if ((i+j)%2 == 1){
                    oled_print_down_shifted(page_credits[j], shiftbits);
                }
                else if ((i+j)%2 == 0) {
                    oled_print_up_shifted(page_credits[j], 8 - shiftbits);
                }
                _delay_ms(500);
            //}
            if ((j)%2 == 0){
                oled_printf(page_credits[j]);
            }
            _delay_ms(500);
        }
			//}
    }/*
		for (int shift_bits = 7; shiftbits > 0; shiftbits--){
    		for (int i = 0; i < NUM_OF_CREDIT_STRINGS; i++){ //iterate through all strings
						oled_clear_screen();
        		for (int j = 0; j < 8; j++){ //iterate through rows
            		if (i+j >= NUM_OF_CREDIT_STRINGS){
                		continue;
            		}
            		oled_goto_line(j);
            		//for (int shiftbits = 7; shiftbits > 0; shiftbits--){ //number of bits shifted
									oled_goto_column(0);
                		if ((i+j)%2 == 1){
                    		oled_print_down_shifted(page_credits[i+j], shiftbits);
                		}
                		else if ((i+j)%2 == 0) {
                    		oled_print_up_shifted(page_credits[i+j], 8 - shiftbits);
                		}
                		_delay_ms(250);
            		//}
            		if ((i+j)%2 == 1){
                		oled_printf(page_credits[i+j]);
            		}
            		_delay_ms(250);
        		}
					}
    }
    _delay_ms(1000);
    #warning go to the previous page at en of function
}*//*
void draw_page_credits(){

			for (int i = 7; i >= 0; i--){
				for (int bit = 0; bit < 8; bit++){
				for (int j = 0; j < 8 - i; j++){
					oled_goto_line(i + j);
					oled_goto_column(0);
					oled_print_up_shifted(page_credits[j], bit);
					//oled_printf(page_credits[j]);
				}
				//oled_sram_update();
				_delay_ms(500);
				oled_clear_screen();
			}
	}
	for (int i = 1; i < NUM_OF_CREDIT_STRINGS; i++){
		for (int j = 0; j < 8 ; j++){
			oled_goto_line(j);
			oled_goto_column(0);
			if (i + j >= NUM_OF_CREDIT_STRINGS){
				break;
			}
			oled_printf(page_credits[i + j]);
		}
		//oled_sram_update();
		_delay_ms(500);
		oled_clear_screen();
	}

}*/
