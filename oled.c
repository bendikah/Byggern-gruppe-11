#include "oled.h"
#define F_CPU 4915200

#include "util/delay.h"
#include "fonts.h"
#include <string.h>


#define OLED_COMMAND    0x1000
#define OLED_DATA       0x1200
#define NUM_OF_PAGES    8
#define NUM_OF_COLUMNS  128

static int current_row;
static int current_col;
static char char_size;


void oled_initialize(void){
    volatile char *oled_int = (char *) OLED_COMMAND;
    *oled_int = 0xae;        //  display  off  
    *oled_int = 0xa1;        //segment  remap  
    *oled_int = 0xda;        //common  pads  hardware:  alternative  
    *oled_int = 0x12;  
    *oled_int = 0xc8;        //common output scan direction:com63~com0 
    *oled_int = 0xa8;        //multiplex  ration  mode:63  
    *oled_int = 0x3f;  
    *oled_int = 0xd5;        //display divide ratio/osc. freq. mode 
    *oled_int = 0x80;          
    *oled_int = 0x81;        //contrast  control    
    *oled_int = 0x50;          
    *oled_int = 0xd9;        //set  pre-charge  period  
    *oled_int = 0x21;          
    *oled_int = 0x20;        //Set  Memory  Addressing  Mode  
    *oled_int = 0x02;          
    *oled_int = 0xdb;        //VCOM  deselect  level  mode  
    *oled_int = 0x30;          
    *oled_int = 0xad;        //master  configuration    
    *oled_int = 0x00;          
    *oled_int = 0xa4;        //out  follows  RAM  content  
    *oled_int = 0xa6;        //set  normal  display  
    *oled_int = 0xaf;        //  display  on  
    //Initialize


    //*oled_int = 0xa5; 
     //*oled_int = 0xa7;

    oled_goto_column(0);
    oled_goto_line(0);
    char_size = 'L';
    oled_fill_screen();
    _delay_ms(1000);
    oled_clear_screen();
    
}


void oled_display_reset(){
    oled_write_c(0xa6);
}

void oled_clear_screen(){
    oled_goto_column(0);
    oled_goto_line(0);
    for (int j = 0; j < NUM_OF_PAGES; j++){
        oled_clear_line(j);
    }
    oled_goto_column(0);
    oled_goto_line(0);
}

void oled_clear_line(int row){
    oled_goto_line(row);
    for (int i = 0;i < NUM_OF_COLUMNS;i++) {
        oled_write_d(0);
    }
}

void oled_fill_screen(){
    oled_goto_line(0);
    oled_goto_column(0);
    for (int j = 0; j < NUM_OF_PAGES; j++){
        oled_goto_line(j);
        for (int i = 0;i < NUM_OF_COLUMNS;i++){
            oled_write_d(0xFF);
        }
    }
    oled_goto_line(0);
    oled_goto_column(0);
}

void oled_write_c(char command){
    volatile char *oled_command = (char *) OLED_COMMAND;
    oled_command[0] = command;
}
void oled_write_d(char data){
    volatile char *oled_data = (char *) OLED_DATA;
    oled_data[0] = data;
}

void oled_goto_line(int line)
{
    current_row = line;
    oled_write_c(0xB0+line);
    
}

void oled_goto_column(int column)
{
    current_col = column;
    int high_terms = (column & 0b11110000) >> 4;
    int low_terms = (column & 0b00001111);
    oled_write_c(0x00+low_terms);
    oled_write_c(0x10+high_terms);
}

void oled_set_char_size(char size){
    char_size = size;
}

int oled_get_char_length(){
    switch(char_size){
        case ('L'): return 8;
        case ('M'): return 5;
        case ('S'): return 4;
        default:    return 4;
    }
}

void oled_put_c(char c){
    if (c == '\n'){
        current_row++;
        current_row %= NUM_OF_PAGES;
        oled_goto_line(current_row);
        oled_goto_column(0);
        return;
    }

    c -= 32; 
    for (int i = 0; i < oled_get_char_length(); i++){
        switch (char_size){
            case ('L'):
                oled_write_d(pgm_read_byte(&(font8[c][i])));
                break;
            case ('M'):
                oled_write_d(pgm_read_byte(&(font5[c][i])));
                break;
            case ('S'):
                oled_write_d(pgm_read_byte(&(font4[c][i])));
                break;
        }
    }
}

void oled_print(char* string){
    for (int i = 0; i < strlen(string); i++){
        oled_put_c(string[i]);
        oled_goto_column(current_col+oled_get_char_length());
        printf("%c",string[i]);
    }
}

void oled_line(int x0, int y0, int x1, int y1){
    //do checks that the values are within the oled display.
    //and happens if 0-value is bigger than 1-value? Than we can just flip the values and everything is fine

    int page0 = y0 / NUM_OF_PAGES;
    int bit0 = y0 % NUM_OF_PAGES;
    int page1 = y1 / NUM_OF_PAGES;
    int bit1 = y1 % NUM_OF_PAGES;

    oled_goto_column(x0);
    oled_goto_line(page0);

    if (x0 == x1){ //line is vertical
        oled_write_d((0b11111111 << bit0) & 0b11111111);
        oled_goto_line(current_row+1);
        for (int i = page0 + 1; i < page1; i++){
            oled_write_d(0b11111111);
            oled_goto_line(current_row+1);
        }
        oled_write_d((0b11111111 >> bit1) & 0b11111111);
    }
    else if (y0 == y1){ //line is horisontal
        for (int i = x0; i <= x1; i++){
            oled_write_d(1 << bit0);
        }
    }
    else{ //line is diagonal
        int dy = y1 - y0;
        int dx = x1 - x0;
        int gradient = ((float)dy)/dx;
        if (dy > dx){
            return;
        }
    }
}

void oled_circle(int x, int y, int r){
    return;
}

