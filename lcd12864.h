#ifndef __LCD12864_H_
#define __LCD12864_H_

void lcd_pos(unsigned char X,unsigned char Y);
void lcd_init();
void lcd_write_data(unsigned char dat);
void lcd_write_cmd(unsigned char cmd);
bit lcd_busy();	
unsigned char read_Byte(void);					   	
void lcd_write_string(unsigned char *s);
void delay(unsigned int i);
#endif