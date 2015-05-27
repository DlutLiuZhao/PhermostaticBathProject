#include"delay.h"

void delay_ms(unsigned int xms)
{
 	unsigned int x = 0;
	unsigned int y = 0;
	for (x = xms; x > 0; --x)
		for (y = 100; y > 0; --y);
}