#ifndef OLED_SRAM_H
#define OLED_SRAM_H
void oled_sram_initialize(void);
uint8_t oled_get_char_length();
void oled_sram_clear_screen(void);
void oled_sram_put_char(uint8_t c);
void oled_sram_fill_screen();
void oled_sram_print(char *string);
void oled_sram_update(void);
void oled_goto_line(int line);
void oled_goto_column(int col);


void oled_sram_print_line(char *string, int shift_bits);
void oled_put_char_line(uint8_t c, int shift_bits);
void oled_sram_set_bit(uint16_t addr, uint8_t bit);
void oled_sram_clear_bit(uint16_t addr, uint8_t bit);
uint8_t oled_sram_read_bit(uint16_t addr, uint8_t bit);
void oled_sram_shift_whole_shit_one_bit();

#endif
