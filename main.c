#include"uart.h"
#include"timer0.h"
#include"delay.h"
#include"lcd12864.h"

void main()
{
	UART_Init();
	Timer0_Init();
	lcd_init();
	lcd_pos(1, 0);
	lcd_write_string("����");
	while (1) {
		SendStr("�����Ǹ�����ˣ�����");
		SendData('\n');
		delay_ms(1000);
	}
}
