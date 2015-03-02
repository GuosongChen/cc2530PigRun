#ifndef HAL_LCD_H
#define HAL_LCD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "hal_types.h"

void transfer_command_lcd(int data1);
void transfer_data_lcd(int data1);
void delay(int n_ms);
void LCD_delay(uint8 ns);
void waitkey();
void initial_lcd();
void lcd_address(uint16 page,uint16 column);
void clear_screen();
void display_128x64(uint8 *dp);
void display_graphic_16x16(uint16 page,uint8 column,uint8 *dp);
void display_graphic_8x16(uint16 page,uint8 column,uint8 *dp);
void display_graphic_5x7(uint16 page,uint8 column,uint8 *dp);
void LCD_write_char( unsigned char c);
void LCD_write_english_string(unsigned char X,unsigned char Y,char *s);
void LCD_disp_char(unsigned char x, unsigned char y, unsigned char c);
void LCD_disp_int(unsigned char x, unsigned char y, unsigned int t);
void LCD_disp_Float (unsigned char x, unsigned char y,float num,unsigned char wei);

#ifdef __cplusplus
}
#endif

#endif

