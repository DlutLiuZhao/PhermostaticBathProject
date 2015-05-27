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
	lcd_write_string("刘钊");
	while (1) {
		SendStr("刘钊是个大好人！！！");
		SendData('\n');
		delay_ms(1000);
	}
}
