#include "include.h"

uint8_t screenMode = 1;
uint8_t i;
char dispBuff[100];
DHT11_Data_TypeDef DHT11_Data;
uint8_t tempState;
uint32_t *p;
uint8_t HUM_ALARM = 90;
uint8_t TEMP_ALARM = 30;

void All_init();
void screen0();
void screen1();
void alarmBeep();
void getValue_and_update();

int main()
{
	All_init();
	while (1)
	{
		wifi_uart_service();
		alarmBeep();
		getValue_and_update();
		KeyFunction();
		switch(screenMode)
		{
			case 0:screen0();break;
			case 1:screen1();break;
			default:break;
		}
	}
}

void All_init()
{
	HUM_ALARM = *(uint32_t *)(0x08000000+2*1024*20);
	TEMP_ALARM = *(uint32_t *)(0x08000000+2*1024*20+10);
	USART_Config();
	wifi_protocol_init();
	Key_GPIO_Config();
	BASIC_TIM_Init();
	LED_GPIO_Config();
	BEEP_Init();
	SysTick_Init();
	OLED_Init();		 //初始化OLED
	DHT11_Init();
}

void alarmBeep()
{
	if (DHT11_Data.humi_int >= HUM_ALARM||DHT11_Data.temp_int>=TEMP_ALARM)
	{
		BEEP_ON;
	}
	else
	{
		BEEP_OFF;
	}
}

void getValue_and_update()
{
	if (DHT11_Read_TempAndHumidity(&DHT11_Data) == SUCCESS)
	{ 
		mcu_dp_value_update(DPID_TEMP_CURRENT,DHT11_Data.temp_int*10+DHT11_Data.temp_deci);
		mcu_dp_value_update(DPID_HUMIDITY_VALUE,DHT11_Data.humi_int);			
	}
}

void screen0()
{
	for (i = 0; i < 7; i++)	OLED_ShowCN(i * 16, 0, i);
	p = (uint32_t *)(0x08000000+2*1024*20);			
	sprintf(dispBuff, "HUM_ALARM:%d", *p);
	OLED_ShowStr(0, 3, (unsigned char *)dispBuff, 2);

	p = (uint32_t *)(0x08000000+2*1024*20+10);
	sprintf(dispBuff, "TEMP_ALARM:%d", *p);
	OLED_ShowStr(0, 5, (unsigned char *)dispBuff, 2);
}

void screen1()
{
	for (i = 0; i < 7; i++)	OLED_ShowCN(i * 16, 0, i);
	if(mcu_get_wifi_work_state()!=tempState) OLED_CLS();
	switch (mcu_get_wifi_work_state())
	{
		case SMART_CONFIG_STATE:sprintf(dispBuff,"%s","SMART_CONFIG_STATE");break;
		case AP_STATE:					sprintf(dispBuff,"%s","AP_STATE");					break;
		case WIFI_NOT_CONNECTED:sprintf(dispBuff,"%s","WIFI_NOT_CONNECTED");break;
		case WIFI_CONNECTED:		sprintf(dispBuff,"%s","WIFI_CONNECTED");		break;
		case WIFI_CONN_CLOUD:		sprintf(dispBuff,"%s","WIFI_CONN_CLOUD");LED1_OFF;LED2_OFF;break;
		case WIFI_LOW_POWER:		sprintf(dispBuff,"%s","WIFI_LOW_POWER");		break;
		case SMART_AND_AP_STATE:sprintf(dispBuff,"%s","SMART_AND_AP_STATE");break;
		case WIFI_SATE_UNKNOW:	sprintf(dispBuff,"%s","WIFI_SATE_UNKNOW");	break;
		default:break;
	}	
	tempState = mcu_get_wifi_work_state();
	OLED_ShowStr(16, 2, (unsigned char *)dispBuff, 1);

	/* 显示温度 */
	for (i = 0; i < 3; i++)	OLED_ShowCN(i * 16, 4, 7 + i);
	sprintf(dispBuff, "%d.%d 'C", DHT11_Data.temp_int, DHT11_Data.temp_deci);
	OLED_ShowStr(45, 4, (unsigned char *)dispBuff, 2);
	/* 显示湿度 */
	for (i = 0; i < 3; i++)	OLED_ShowCN(i * 16, 6, 10 + i);
	sprintf(dispBuff, "%d.%d% %RH", DHT11_Data.humi_int, DHT11_Data.humi_deci);
	OLED_ShowStr(45, 6, (unsigned char *)dispBuff, 2);
}
/***********************************END OF FILE*********************************/
