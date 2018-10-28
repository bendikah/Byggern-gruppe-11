#ifndef OLED_SRAM_H
#define OLED_SRAM_H
void oled_sram_initialize(void);
uint8_t oled_get_char_length();
void oled_sram_clear_screen(void);
void oled_sram_put_char(uint8_t c);
void oled_fill_screen_horizontal();
void oled_sram_print(char *string);
void oled_sram_update(void);
#endif
