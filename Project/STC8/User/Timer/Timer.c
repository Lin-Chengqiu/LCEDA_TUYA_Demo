#include "./Timer/Timer.h"

void Timer4Init(void)		//1毫秒@24.000MHz
{
	T4T3M |= 0x20;		//定时器时钟1T模式
	T4L = 0x40;		//设置定时初值
	T4H = 0xA2;		//设置定时初值
	T4T3M |= 0x80;		//定时器4开始计时
	IE2 |= ET4;        //使能定时器中断
	EA = 1;
}

void TM4_Isr() interrupt 20
{
	static unsigned int ms = 0;
	if(++ms == 1000)
	{
		ms = 0;
		Flash_Led();
	}
}