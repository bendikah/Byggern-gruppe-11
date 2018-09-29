#ifndef OLED_H
#define OLED_H


void oled_initialize(void);
void oled_write(char c);
void oled_display_reset();
void oled_clear();
void oled_write_c(char command);
void oled_write_d(char data);
//void printthis(void);

#endif

