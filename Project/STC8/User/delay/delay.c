#include "./delay/delay.h"


void Delay1us()		//@24.000MHz
{
	unsigned char i;

	i = 6;
	while (--i);
}

void Delay1ms()		//@24.000MHz
{
	unsigned char i, j;

	_nop_();
	i = 32;
	j = 40;
	do
	{
		while (--j);
	} while (--i);
}

void Delay_us ( uint16_t us )
{ 
	uint16_t i;
	for( i = 0 ;i<us;i++)
	{
		Delay1us();
	}
}

void Delay_ms ( uint16_t ms )
{ 
	uint16_t i;
	for( i = 0 ;i<ms;i++)
	{
		Delay1ms();
	}
}

/*********************************************END OF FILE**********************/
