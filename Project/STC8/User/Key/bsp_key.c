#include "./key/bsp_key.h"  


void Key_init(void)
{
	P3M1=(P3M1&0x3F)|0xC0;  //设置IO口模式
	P3M0=(P3M0&0x3F)|0xC0;  //设置IO口模式
	/*
	P3.0维持不变
	P3.1维持不变
	P3.2维持不变
	P3.3维持不变
	P3.4维持不变
	P3.5维持不变
	P3.6开漏
	P3.7开漏
	*/
}

void KeyScan(void)
{
	static uint8_t OLED_Light = 1;
	static uint8_t LedEnable = 0;
	if (KEY1 == KEY_ON)
	{
		LedEnable = !LedEnable;
		if(LedEnable)
		{
			IE2 |= ET4;
		}
		else
		{
			IE2 &= ~ET4;
			LED_R_OFF;LED_G_OFF;LED_B_OFF;
		}
	}while(KEY1 == KEY_ON);
	if (KEY2 == KEY_ON)
	{
		OLED_Light = !OLED_Light;
		if(OLED_Light)
			OLED_ON();
		else
			OLED_OFF();
	}while(KEY2 == KEY_ON);
}
/*********************************************END OF FILE**********************/
