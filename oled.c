#include "oled.h"

#include "util/delay.h"

#define OLED_SPACE 0x1000
#define OLED_WRITE 0x1200

void oled_initialize(void){
    volatile char *oled_int = (char *) OLED_SPACE;
    *oled_int =0xae;        //  display  off
      _delay_ms(500);
    *oled_int =0xa1;        //segment  remap
    *oled_int =0xda;        //common  pads  hardware:  alternative
    *oled_int =0x12;
    *oled_int =0xc8;        //common output scan direction:com63~com0
    *oled_int =0xa8;        //multiplex  ration  mode:63
    *oled_int =0x3f;
    *oled_int =0xd5;        //display divide ratio/osc. freq. mode
    *oled_int =0x80;
    *oled_int =0x81;        //contrast  control
    *oled_int =0x50;
    *oled_int =0xd9;        //set  pre-charge  period
    *oled_int =0x21;
    *oled_int =0x20;        //Set  Memory  Addressing  Mode
    *oled_int =0x02;
    *oled_int =0xdb;        //VCOM  deselect  level  mode
    *oled_int =0x30;
    *oled_int =0xad;        //master  configuration
    *oled_int =0x00;
    *oled_int =0xa4;        //out  follows  RAM  content
    *oled_int =0xa6;        //set  normal  display

    *oled_int =0xaf;        //  display  on
}

//void printthis(void){
  //  printf("hei");
//}
void oled_write(char c){
    volatile char *oled_write = (char *) OLED_WRITE;
      while(1){
      *oled_write = c;
}
}
