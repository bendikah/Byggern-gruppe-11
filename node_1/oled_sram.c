
//#define F_CPU 4915200
#include "global_defines.h"
#include "util/delay.h"
#include "fonts.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>
#include "sram.h"


#define OLED_COMMAND    0x1000
#define OLED_DATA       0x1200
#define NUM_OF_PAGES    8
#define NUM_OF_COLUMNS  128

static uint8_t current_row;
static uint8_t current_col;
static uint8_t char_size;

void oled_sram_initialize(void){
    volatile uint8_t *oled_int = (uint8_t *) OLED_COMMAND;
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

    // start Addressing Mode
    *oled_int = 0x20;
    *oled_int = 0x00;
    *oled_int = 0x22;
    *oled_int = 0x00;
    *oled_int = 0x07;
    char_size = 'L';
    current_col = 0;
    current_row = 0;
}

void oled_sram_clear_screen(void){
  for (int i = 0; i < 1024; i++){
    sram_write(i,0);
  }
}

uint8_t oled_get_char_length(){
    switch(char_size){
        case ('L'): return 8;
        case ('M'): return 5;
        case ('S'): return 4;
        default:    return 4;
    }
}

void oled_sram_put_char(uint8_t c){
  if (c == '\n'){
      current_row++;
      current_row %= NUM_OF_PAGES;
      current_col = 0;
      return;
  }
    c -= 32;
    for (uint8_t i = 0; i < oled_get_char_length(); i++){
        switch (char_size){
            case ('L'):
                sram_write(current_row*NUM_OF_COLUMNS + current_col, pgm_read_byte(&(font8[c][i])));
                break;
            case ('M'):
                sram_write(current_row*NUM_OF_COLUMNS + current_col, pgm_read_byte(&(font5[c][i])));
                break;
            case ('S'):
                sram_write(current_row*NUM_OF_COLUMNS + current_col, pgm_read_byte(&(font4[c][i])));
                break;
        }
        current_col++;
    }
}

void oled_sram_fill_screen(){
  for (int i = 0; i < 1024; i++){
    sram_write(i,0xff);
  }
}


void oled_sram_print(char *string){
    /* 0 int i = 0;
    while(data[i] != '\0'){
      oled_sram_put_char(data[i]);
      i++;
    }*/
    for (uint8_t i = 0; i < strlen(string); i++){
        oled_sram_put_char(string[i]);
    }
}

void oled_sram_update(void){
    volatile uint8_t *oled_data = (uint8_t *) OLED_DATA;
    for (int i = 0; i < 1024; i++){
      *oled_data = sram_read(i);
    }
    current_row = 0;
    current_col = 0;
}



void oled_goto_line(uint8_t line)
{
    current_row = line;

}

void oled_goto_column(uint8_t column)
{
    current_col = column;
}




uint8_t oled_sram_read_bit(uint16_t addr, uint8_t bit){
  uint8_t val = 1<<bit;
  uint8_t temp = sram_read(addr);
  return !!(temp & val);
}

void oled_sram_set_bit(uint16_t addr, uint8_t bit){
  uint8_t val = 1<<bit;
  uint8_t temp = sram_read(addr);
  sram_write(addr,temp | val);
}

void oled_sram_clear_bit(uint16_t addr, uint8_t bit){
  uint8_t val = 1<<bit;
  uint8_t temp = sram_read(addr);
  sram_write(addr,temp & ~val);
}


void oled_put_char_line(uint8_t c, int line){

    c -= 32;
    for (uint8_t i = 0; i < oled_get_char_length(); i++){
        switch (char_size){
            case ('L'):
                sram_write(current_row*NUM_OF_COLUMNS + current_col, pgm_read_byte(&(font8[c][i])) <<line);
                break;
            case ('M'):
                sram_write(current_row*NUM_OF_COLUMNS + current_col, pgm_read_byte(&(font5[c][i])));
                break;
            case ('S'):
                sram_write(current_row*NUM_OF_COLUMNS + current_col, pgm_read_byte(&(font4[c][i])));
                break;
        }
        current_col++;
    }
}

void oled_sram_print_line(char *string, int line){
  for (uint8_t i = 0; i < strlen(string); i++){
      oled_put_char_line(string[i], line);
      //oled_goto_column(current_col+oled_get_char_length());
  }
}

void oled_sram_shift_whole_shit_one_bit(){
  for (uint16_t i = 0; i < 1024; i++){
    if (i >= 128) {
      if (test_bit(sram_read(i),0)){
//      if (oled_sram_read_bit(i,7)){
        oled_sram_set_bit(i-128,7);
      }
      else {
        oled_sram_clear_bit(i-128,7);
      }
    }
    sram_write(i, sram_read(i) >> 1);
  }
}
