#include"uart.h"
#include"timer0.h"
#include"delay.h"

void main()
{
	UART_Init();
	Timer0_Init();
	while (1) {
		SendStr("�����Ǹ�����ˣ�����");
		SendData('\n');
		delay_ms(1000);
	}
}
