#ifndef OLED_H
#define OLED_H

#include <avr/io.h>

void oled_initialize(void);
void oled_write(uint8_t c);
void oled_display_reset();
void oled_clear_line(uint8_t row);
void oled_clear_screen();
void oled_fill_screen();
void oled_write_c(uint8_t command);
void oled_write_d(uint8_t data);
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_set_char_size(uint8_t size);
uint8_t oled_get_char_length();
void oled_put_c(uint8_t c);
__attribute__((format(printf,1,2))) void oled_printf(const char* fmt, ...);





#endif
