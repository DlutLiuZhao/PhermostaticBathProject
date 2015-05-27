#include"uart.h"
#include"stc12c5a60s2.h"

#define   FOSC      16000000L
#define   BAUD      9600	//19200	57600	14400	9600	  

//初始化串口
void UART_Init(void)
{
//	AUXR|=T1x12;    //1T模式
	SCON |= 0x5a;                    
    TMOD |= 0x20; 
    TH1 = TL1 = 247;
    TR1 = 1;  
}

void SendData(unsigned char dat)
{
      while (!TI);                        //Wait for the previous data is sent
      TI = 0;                             //Clear TI flag
      SBUF = dat;                         //Send current data
}
unsigned char ReceiveData(void)
{
	while (!RI);                        //Wait for the previous data is sent
    RI = 0;                             //Clear TI flag
   	return SBUF;                        //Send current data	
}

void SendStr(const char* str)
{
 	while (*str != '\0') {
		SendData(*str);
		++str;
	}
}