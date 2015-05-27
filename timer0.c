#include"timer0.h"
#include"stc12c5a60s2.h"

sbit LED = P1^2;

void Timer0_Init()
{
	TMOD |= 0x01;
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void Timer0_ISR() interrupt 1
{
  static int count = 0;
  ++ count;
  if (count == 5) {
   	count = 0;
	LED = ~LED;
  }
}