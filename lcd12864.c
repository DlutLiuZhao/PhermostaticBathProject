#include "lcd12864.h"
#include "delay.h"
#include "stc12c5a60s2.h"

#ifndef LCD12864_SERIAL_FORMAT
/* LCD 12864 Pin */
#define LCD12864_DATA P0   	 // 并行数据口
sbit	LCD12864_RS = P3^5;  // 并行的指令/数据选择信号；
sbit 	LCD12864_WR = P3^6;  // 并行的读写选择信号；
sbit 	LCD12864_EN = P3^4;  // 并行的使能信号；
sbit 	LCD12864_RD = P3^7;  // 并/串行接口选择； H-并行 L-串行
#else
sbit 	LCD12864_CS  = P3^5;	 // 串行的片选信号
sbit 	LCD12864_WR  = P3^6;	 // 串行的数据口
sbit	LCD12864_CLK = P3^7;	 // 串行的同步时钟
#endif

const char CMD_CLEAR_DISPLAY = 0X01; //清屏
const char CMD_BASIC_INSTRUCTION = 0X30; //基本指令集
const char CMD_EXTEND_INSTRUCTION = 0X34; //扩充指令集
const char CMD_DISPLAY_ALL_ON = 0X0C; //整体显示ON
const char CMD_DISPLAY_CURSOR_ON = 0X0A; //游标ON
const char CMD_CURSOR_POSITION = 0X09; //游标位置ON



/*******************************************************************/
/*                                                                 */
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
/*                                                                 */
/*******************************************************************/
#ifndef LCD12864_SERIAL_FORMAT
bit lcd_busy()
{                          
	bit result;
    LCD12864_RS = 0;
    LCD12864_WR = 1;
    LCD12864_EN = 1;
	delay_ms(2);
    result = (bit)(P0&0x80);
    LCD12864_EN = 0;
    return(result); 
}
 #else
bit lcd_busy()
{
 	bit result;

	return result;
}
 #endif
/*******************************************************************/
/*                                                                 */
/*读数据                                                    */
/*                                                                 */
/*******************************************************************/
#ifndef LCD12864_SERIAL_FORMAT
unsigned char read_Byte(void)
{
	unsigned char read=0;
	while(lcd_busy());
    LCD12864_RS = 1;
    LCD12864_WR = 1;
	LCD12864_DATA=0xff;
    LCD12864_EN = 1;
	delay_ms(2);
	read=LCD12864_DATA;
	LCD12864_EN = 0;
	return read;
}
#else
unsigned char read_Byte(void)
{
 	unsigned char read = 0;

	return read;
}
#endif

/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/

#ifndef LCD12864_SERIAL_FORMAT
void lcd_write_cmd(unsigned char cmd)
{                          
   while(lcd_busy());
    LCD12864_RS = 0;
    LCD12864_WR = 0;
    LCD12864_EN = 0;
    LCD12864_DATA = cmd;
    delay_ms(2);
    LCD12864_EN = 1;
    delay_ms(2);
    LCD12864_EN = 0;  
}
#else
void lcd_write_cmd(unsigned char cmd)
{

}
#endif
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
#ifndef LCD12864_SERIAL_FORMAT
void lcd_write_data(unsigned char dat)
{                          
   while(lcd_busy());
    LCD12864_RS = 1;
    LCD12864_WR = 0;
    LCD12864_EN = 0;
    LCD12864_DATA = dat;
	delay_ms(2);
    LCD12864_EN = 1;
	delay_ms(2);
    LCD12864_EN = 0; 
}
#else 
void lcd_write_data(unsigned char dat)
{

}
#endif
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD12864_RD = 1;         //并口方式 
    //lcd_write_cmd(0x34);      //扩充指令操作
    //delay_ms(5);
    lcd_write_cmd(0x30);      //基本指令操作
    delay_ms(1);
    lcd_write_cmd(0x0c);      //显示开，关光标
    delay_ms(5);
    lcd_write_cmd(0x01);      //清除LCD的显示内容
    delay_ms(5);
}

void clear_lcd()
{	
	unsigned char i,j;
	lcd_write_cmd(0x34);
	for(i=0;i<32;i++)			  //因为LCD有纵坐标32格所以写三十二次
	{
		lcd_write_cmd(0x80+i);		  //先写入纵坐标Y的值
		lcd_write_cmd(0x80);		  //再写入横坐标X的值
		for(j=0;j<32;j++)		  //横坐标有16位，每位写入两个字节的的数据，也就写入32次
		{						  //因为当写入两个字节之后横坐标会自动加1，所以就不用再次写入地址了。
			lcd_write_data(0x00);	  
		}
	}
	lcd_write_cmd(0x36);
	lcd_write_cmd(0x30);
}

/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(unsigned char X,unsigned char Y)
{                          
   unsigned char  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   lcd_write_cmd(pos);     //显示地址
}
void lcd_write_string(unsigned char *s)
{
	while(*s!='\0')
	{
		lcd_write_data(*s);
		s++;	
	}
}