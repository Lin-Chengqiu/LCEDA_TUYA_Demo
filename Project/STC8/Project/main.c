#include "include.h"

uint8_t i;
uint8_t dispBuff[100];
DHT11_Data_TypeDef DHT11_Data;
uint8_t tempState;
uint8_t a = 20;
void All_init();
void screen();
void getValue_and_update();

int main()
{
	All_init();
	while (1)
	{
		wifi_uart_service();
		getValue_and_update();
		KeyScan();
		screen();
	}
}

void All_init()
{
	LED_init();
	Key_init();
	Timer4Init();	
	UartDebugInit();
	Uart3Init();
	wifi_protocol_init();
	OLED_Init();
	DHT11_Init();	
}

void getValue_and_update()
{
	if (DHT11_Read_TempAndHumidity(&DHT11_Data) == SUCCESS)
	{ 
		mcu_dp_value_update(DPID_TEMP_CURRENT,DHT11_Data.temp_int*10+DHT11_Data.temp_deci);
		mcu_dp_value_update(DPID_HUMIDITY_VALUE,DHT11_Data.humi_int);			
	}
}

void screen()
{
	for (i = 0; i < 7; i++)	OLED_ShowCN(i * 16, 0, i);
	if(mcu_get_wifi_work_state()!=tempState) OLED_CLS();
	switch (mcu_get_wifi_work_state())
	{
		case SMART_CONFIG_STATE:sprintf(dispBuff,"%s","SMART_CONFIG_STATE");break;
		case AP_STATE:					sprintf(dispBuff,"%s","AP_STATE");					break;
		case WIFI_NOT_CONNECTED:sprintf(dispBuff,"%s","WIFI_NOT_CONNECTED");break;
		case WIFI_CONNECTED:		sprintf(dispBuff,"%s","WIFI_CONNECTED");		break;
		case WIFI_CONN_CLOUD:		sprintf(dispBuff,"%s","WIFI_CONN_CLOUD");		break;
		case WIFI_LOW_POWER:		sprintf(dispBuff,"%s","WIFI_LOW_POWER");		break;
		case SMART_AND_AP_STATE:sprintf(dispBuff,"%s","SMART_AND_AP_STATE");break;
		case WIFI_SATE_UNKNOW:	sprintf(dispBuff,"%s","WIFI_SATE_UNKNOW");	break;
		default:break;
	}	
	tempState = mcu_get_wifi_work_state();
	OLED_ShowStr(16, 2, (uint8_t *)dispBuff, 1);

	/* 显示温度 */
	for (i = 0; i < 3; i++)	OLED_ShowCN(i * 16, 4, 7 + i);
	sprintf(dispBuff, "%bd.%bd 'C", DHT11_Data.temp_int, DHT11_Data.temp_deci);
	OLED_ShowStr(45, 4, (uint8_t *)dispBuff, 2);
	/* 显示湿度 */
	for (i = 0; i < 3; i++)	OLED_ShowCN(i * 16, 6, 10 + i);
	sprintf(dispBuff, "%bd.%bd% %RH", DHT11_Data.humi_int, DHT11_Data.humi_deci);
	OLED_ShowStr(45, 6, (uint8_t *)dispBuff, 2);
}