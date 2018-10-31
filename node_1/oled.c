#include "oled.h"
#define F_CPU 4915200

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

static FILE oled_io = FDEV_SETUP_STREAM(oled_put_c, NULL, _FDEV_SETUP_WRITE);


void oled_initialize(void){
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
    /**oled_int = 0x20;
    *oled_int = 0x00;
    *oled_int = 0x22;
    *oled_int = 0x00;
    *oled_int = 0x07;
*/
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
    for (uint8_t j = 0; j < NUM_OF_PAGES; j++){
        oled_clear_line(j);
    }
    oled_goto_column(0);
    oled_goto_line(0);
}

void oled_clear_line(uint8_t row){
    oled_goto_line(row);
    for (uint8_t i = 0;i < NUM_OF_COLUMNS;i++) {
        oled_write_d(0);
    }
}

void oled_fill_screen(){
    oled_goto_line(0);
    oled_goto_column(0);
    for (uint8_t j = 0; j < NUM_OF_PAGES; j++){
        oled_goto_line(j);
        for (uint8_t i = 0;i < NUM_OF_COLUMNS;i++){
            oled_write_d(0xFF);
        }
    }
    oled_goto_line(0);
    oled_goto_column(0);
}

void oled_write_c(uint8_t command){
    volatile uint8_t *oled_command = (uint8_t *) OLED_COMMAND;
    oled_command[0] = command;
}
void oled_write_d(uint8_t data){
    volatile uint8_t *oled_data = (uint8_t *) OLED_DATA;
    oled_data[0] = data;
}

void oled_goto_line(uint8_t line)
{
    current_row = line;
    oled_write_c(0xB0+line);

}

void oled_goto_column(uint8_t column)
{
    current_col = column;
    uint8_t high_terms = (column & 0b11110000) >> 4;
    uint8_t low_terms = (column & 0b00001111);
    oled_write_c(0x00+low_terms);
    oled_write_c(0x10+high_terms);
}

void oled_set_char_size(uint8_t size){
    char_size = size;
}

uint8_t oled_get_char_length(){
    switch(char_size){
        case ('L'): return 8;
        case ('M'): return 5;
        case ('S'): return 4;
        default:    return 4;
    }
}

void oled_put_c(uint8_t c){
    if (c == '\n'){
        current_row++;
        current_row %= NUM_OF_PAGES;
        oled_goto_line(current_row);
        oled_goto_column(0);
        return;
    };
    c -= 32;
    for (uint8_t i = 0; i < oled_get_char_length(); i++){
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

void oled_printf(const char* fmt, ...){
  va_list args;
  va_start(args, fmt);
  vfprintf(&oled_io, fmt, args);
  va_end(args);
}

void oled_put_char_up_shifted(uint8_t c, int shift_bits){
  if (c == '\n'){
      current_row++;
      current_row %= NUM_OF_PAGES;
      oled_goto_line(current_row);
      oled_goto_column(0);
      return;
  };
  c -= 32;
  for (uint8_t i = 0; i < oled_get_char_length(); i++){
      switch (char_size){
          case ('L'):
              oled_write_d((pgm_read_byte(&(font8[c][i]))) >> shift_bits);
              break;
          case ('M'):
              oled_write_d((pgm_read_byte(&(font5[c][i]))) >> shift_bits);
              break;
          case ('S'):
              oled_write_d((pgm_read_byte(&(font4[c][i]))) >> shift_bits);
              break;
      }
  }
}
void oled_put_char_down_shifted(uint8_t c, int shift_bits){
  if (c == '\n'){
      current_row++;
      current_row %= NUM_OF_PAGES;
      oled_goto_line(current_row);
      oled_goto_column(0);
      return;
  };
  c -= 32;
  for (uint8_t i = 0; i < oled_get_char_length(); i++){
      switch (char_size){
          case ('L'):
              oled_write_d((pgm_read_byte(&(font8[c][i]))) << shift_bits);
              break;
          case ('M'):
              oled_write_d((pgm_read_byte(&(font5[c][i]))) << shift_bits);
              break;
          case ('S'):
              oled_write_d((pgm_read_byte(&(font4[c][i]))) << shift_bits);
              break;
      }
  }
}

void oled_print_up_shifted(uint8_t* string, int shift_bits){
  for (uint8_t i = 0; i < strlen(string); i++){
      oled_put_char_up_shifted(string[i], shift_bits);
      //oled_goto_column(current_col+oled_get_char_length());
  }
}
void oled_print_down_shifted(uint8_t* string, int shift_bits){
  for (uint8_t i = 0; i < strlen(string); i++){
      oled_put_char_up_shifted(string[i], shift_bits);
      //oled_goto_column(current_col+oled_get_char_length());
  }
}

/*
void oled_print(uint8_t* string){
    for (uint8_t i = 0; i < strlen(string); i++){
        oled_put_c(string[i]);
        oled_goto_column(current_col+oled_get_char_length());
        USART_printf("%c",string[i]);
    }
}*/

/*-------------Under her is oled writing through the sram------------------*/
/*

void oled_sram_put_noise(void){ //aha..... hva er denne funksjonen for? Er ikek dette bare en clear sram_screen?
  for (int i =0; i < 8; i++){
    for(int j = 0; j < 128; j++){
      sram_write(i*128+j,1);
    }
  }
}

void oled_sram_clear_screen(void){
  for (int i = 0; i < 1024; i++){
    sram_write(i,0);
  }
}

void oled_sram_put_char(uint8_t c){

    //oled_put_c(c);
    /*c -= 32;
    for(int i =0; i < 8; i++){
      sram_write(current_row*128+current_col + i, pgm_read_byte(&font8[c][i]));
    }
    if (c == '\n'){
        current_row++;
        current_row %= NUM_OF_PAGES;
        oled_goto_line(current_row);
        oled_goto_column(0);
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
        USART_printf("Im in oled_sram_put_c and putting a byte\n");
        USART_printf("row: %i, col: %i\n",current_row, current_col);
        current_col++;
    }
}

void oled_fill_screen_horizontal(){
  volatile uint8_t *oled_data = (uint8_t *) OLED_DATA;
  for (int i = 0; i < 1024; i++){
    *oled_data = 0xff;
  }
}


void oled_sram_print(char *string){
    /* 0 int i = 0;
    while(data[i] != '\0'){
      oled_sram_put_char(data[i]);
      i++;
    }
    for (uint8_t i = 0; i < strlen(string); i++){
        oled_sram_put_char(string[i]);
    }
}

void oled_sram_update(void){
    oled_clear_screen();
    volatile uint8_t *oled_data = (uint8_t *) OLED_DATA;
    uint8_t temp;
    /*for (int i = 0; i < 1024; i++){
      *oled_data = sram_read(i);
    }
    for (int i =0; i < 8; i++){
      //USART_printf("%i \n",sram_read(i*128));
      for(int j = 0; j < 128; j++){
        temp = sram_read(i*128+j);
        *oled_data = temp;
      }
    }
}
*/
