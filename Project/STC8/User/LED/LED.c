#include "./LED/LED.h"

void LED_init(void)
{
	/*
	P5.4推挽
	P5.5推挽
	*/	
	P5M1=(P5M1&0xCF)|0x00;  //设置IO口模式
	P5M0=(P5M0&0xCF)|0x30;  //设置IO口模式
	/*P4.0推挽*/
	P4M1=(P4M1&0xFE)|0x00;  //设置IO口模式
	P4M0=(P4M0&0xFE)|0x01;  //设置IO口模式
}

void Flash_Led(void)
{
	static unsigned char count = 0;     //LED标志位
	switch(++count)
	{
		case 1: LED_R_ON;LED_G_OFF;LED_B_OFF;break;//点亮LED1
		case 2: LED_R_OFF;LED_G_ON;LED_B_OFF;break;//点亮LED2s
		default :LED_R_OFF;LED_G_OFF;LED_B_ON;count = 0; break;
	}
}