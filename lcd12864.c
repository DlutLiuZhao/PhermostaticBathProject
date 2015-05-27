#include "lcd12864.h"
#include "delay.h"
#include "stc12c5a60s2.h"

#ifndef LCD12864_SERIAL_FORMAT
/* LCD 12864 Pin */
#define LCD12864_DATA P0   	 // �������ݿ�
sbit	LCD12864_RS = P3^5;  // ���е�ָ��/����ѡ���źţ�
sbit 	LCD12864_WR = P3^6;  // ���еĶ�дѡ���źţ�
sbit 	LCD12864_EN = P3^4;  // ���е�ʹ���źţ�
sbit 	LCD12864_RD = P3^7;  // ��/���нӿ�ѡ�� H-���� L-����
#else
sbit 	LCD12864_CS  = P3^5;	 // ���е�Ƭѡ�ź�
sbit 	LCD12864_WR  = P3^6;	 // ���е����ݿ�
sbit	LCD12864_CLK = P3^7;	 // ���е�ͬ��ʱ��
#endif

const char CMD_CLEAR_DISPLAY = 0X01; //����
const char CMD_BASIC_INSTRUCTION = 0X30; //����ָ�
const char CMD_EXTEND_INSTRUCTION = 0X34; //����ָ�
const char CMD_DISPLAY_ALL_ON = 0X0C; //������ʾON
const char CMD_DISPLAY_CURSOR_ON = 0X0A; //�α�ON
const char CMD_CURSOR_POSITION = 0X09; //�α�λ��ON



/*******************************************************************/
/*                                                                 */
/*���LCDæ״̬                                                    */
/*lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ�      */
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
/*������                                                    */
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
/*дָ�����ݵ�LCD                                                  */
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣                             */
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
/*д��ʾ���ݵ�LCD                                                  */
/*RS=H��RW=L��E=�����壬D0-D7=���ݡ�                               */
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
/*  LCD��ʼ���趨                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 

    LCD12864_RD = 1;         //���ڷ�ʽ 
    //lcd_write_cmd(0x34);      //����ָ�����
    //delay_ms(5);
    lcd_write_cmd(0x30);      //����ָ�����
    delay_ms(1);
    lcd_write_cmd(0x0c);      //��ʾ�����ع��
    delay_ms(5);
    lcd_write_cmd(0x01);      //���LCD����ʾ����
    delay_ms(5);
}

void clear_lcd()
{	
	unsigned char i,j;
	lcd_write_cmd(0x34);
	for(i=0;i<32;i++)			  //��ΪLCD��������32������д��ʮ����
	{
		lcd_write_cmd(0x80+i);		  //��д��������Y��ֵ
		lcd_write_cmd(0x80);		  //��д�������X��ֵ
		for(j=0;j<32;j++)		  //��������16λ��ÿλд�������ֽڵĵ����ݣ�Ҳ��д��32��
		{						  //��Ϊ��д�������ֽ�֮���������Զ���1�����ԾͲ����ٴ�д���ַ�ˡ�
			lcd_write_data(0x00);	  
		}
	}
	lcd_write_cmd(0x36);
	lcd_write_cmd(0x30);
}

/*********************************************************/
/*                                                       */
/* �趨��ʾλ��                                          */
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
   lcd_write_cmd(pos);     //��ʾ��ַ
}
void lcd_write_string(unsigned char *s)
{
	while(*s!='\0')
	{
		lcd_write_data(*s);
		s++;	
	}
}