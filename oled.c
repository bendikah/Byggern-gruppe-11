#include "oled.h"

#include "util/delay.h"
#include "fonts.h"


#define OLED_COMMAND 0x1000 //why space and write, why not command and data?
#define OLED_DATA 0x1200

void oled_initialize(void){
    volatile char *oled_int = (char *) OLED_COMMAND; //why not oled write
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


    *oled_int = 0xB0; // sets the page start address to upper left?
    *oled_int = 0x00;
    *oled_int = 0x10;
}


void oled_display_reset(){
    volatile char *oled_int = (char *) OLED_COMMAND;
    *oled_int = 0xa6;
}


/*
void oled_goto_column(){
    volatile char *oled_int = (char *) OLED_COMMAND;
    *oled_int = 0xB0; // sets the page start address to upper left?
    *oled_int = 0x00;
    *oled_int = 0x1F;


}
*/

void oled_clear(){
    volatile char *oled_int = (char *) OLED_COMMAND;
    *oled_int = 0xB0; // sets the page start address to upper left?
    *oled_int = 0x00;
    *oled_int = 0x10;

    volatile char *oled_write = (char *) OLED_DATA;
    for (int j = 0; j <7; j++){
        for (int i = 0;i <128;i++){
            *oled_write =0x00;
    }
}
}

void oled_write(char c){ 
    
    volatile char *oled_writel = (char *) OLED_DATA;
    *oled_writel = 0;
    
    //*oled_writel = c;
    /* *oled_write =0b00000110;
    *oled_write =0b01011111;
    *oled_write =0b01011111;
    *oled_write =0b01011111;
    *oled_write =0b00000000;
    *oled_write =0b00000000; 
    *oled_write =0b00000000;*/
}
