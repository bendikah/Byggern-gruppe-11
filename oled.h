#ifndef OLED_H
#define OLED_H


void oled_initialize(void);
void oled_write(char c);
void oled_display_reset();
void oled_clear_line(int row);
void oled_clear_screen();
void oled_fill_screen();
void oled_write_c(char command);
void oled_write_d(char data);
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_set_char_size(char size);
int oled_get_char_length();
void oled_put_c(char c);
void oled_print(char* string);

void oled_line(int x0, int y0, int x1, int y1);
void oled_circle(int x, int y, int r);


#endif

