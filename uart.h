#ifndef __UART_H
#define __UART_H

void UART_Init(void);
void SendData(unsigned char dat);
unsigned char ReceiveData(void);
void SendStr(const char* str);


#endif