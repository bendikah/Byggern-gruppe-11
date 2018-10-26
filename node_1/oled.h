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



void oled_sram_put_char(uint8_t c);
void oled_sram_print(uint8_t *data);
void oled_sram_put_noise(void);

void oled_sram_update(void);

/*
 * Put_char functions below should be static in the c-file
 */
void oled_sram_put_char_up_shifted(uint8_t c, int shift_bits);
void oled_sram_put_char_down_shifted(uint8_t c, int shift_bits);

void oled_sram_print_up_shifted(uint8_t* data, int shift_bits);
void oled_sram_print_down_shifted(uint8_t* data, int shift_bits);

#endif
