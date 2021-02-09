/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   按键应用bsp（扫描模式）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./key/bsp_key.h"  

/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK|KEY3_GPIO_CLK|KEY4_GPIO_CLK,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY3_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY3_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY4_GPIO_PIN; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(KEY4_GPIO_PORT, &GPIO_InitStructure);	
}

 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 
		/*等待按键释放 */
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}
extern uint8_t screenMode;
extern uint8_t HUM_ALARM;
extern uint8_t TEMP_ALARM;
uint8_t AlarmSelect = 0;
uint8_t OLED_Light = 1;
void KeyFunction(void)
{
	static 	uint8_t wifiMode = 0;
	static uint8_t LedEnable = 0;
	switch(screenMode)
	{
		case 0:
		{
			if(!AlarmSelect)
			{
				OLED_ShowStr(110, 3,(unsigned char *)"<-",2);
			}
			else
			{
				OLED_ShowStr(110, 5,(unsigned char *)"<-",2);
			}
			if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON)
			{
				OLED_CLS();
				AlarmSelect = !AlarmSelect;
			}
			if (Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON)
			{
				OLED_CLS();			 //清屏
				screenMode++;
			}
			if (Key_Scan(KEY3_GPIO_PORT, KEY3_GPIO_PIN) == KEY_ON)
			{
				OLED_CLS();
				if(!AlarmSelect)
				{
					HUM_ALARM-=5;
					if(HUM_ALARM<5)	HUM_ALARM = 90;
				}
				else
				{
					TEMP_ALARM--;
					if(TEMP_ALARM<10)	TEMP_ALARM = 40;
				}
				FLASH_Unlock();
				FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
				//擦除
				FLASH_ErasePage(0x08000000+2*1024*20);
				
				//写入数据
				FLASH_ProgramWord(0x08000000+2*1024*20,HUM_ALARM);
				FLASH_ProgramWord(0x08000000+2*1024*20+10,TEMP_ALARM);
				FLASH_Lock();
			}
			if (Key_Scan(KEY4_GPIO_PORT, KEY4_GPIO_PIN) == KEY_ON)
			{
				OLED_CLS();
				if(!AlarmSelect)
				{
					HUM_ALARM+=5;
					if(HUM_ALARM>90)	HUM_ALARM = 5;
				}
				else
				{
					TEMP_ALARM++;
					if(TEMP_ALARM>40)	TEMP_ALARM = 10;
				}
				FLASH_Unlock();
				FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);//清除标志位
				//擦除
				FLASH_ErasePage(0x08000000+2*1024*20);
				
				//写入数据
				FLASH_ProgramWord(0x08000000+2*1024*20,HUM_ALARM);
				FLASH_ProgramWord(0x08000000+2*1024*20+10,TEMP_ALARM);
				FLASH_Lock();
			}
		};break;
		case 1:
		{
			if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON)
			{
				wifiMode++;
				switch(wifiMode)
				{
					case 1:mcu_set_wifi_mode(SMART_CONFIG);LED1_ON;break;
					case 2:mcu_set_wifi_mode(AP_CONFIG);LED2_ON;LED1_OFF;break;
					default:wifiMode = 0;;LED2_OFF;break;
				}
			}
			if (Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON)
			{
				OLED_CLS();			 //清屏
				screenMode++;
			}
			if (Key_Scan(KEY3_GPIO_PORT, KEY3_GPIO_PIN) == KEY_ON)
			{
				OLED_Light = !OLED_Light;
				if(OLED_Light)
					OLED_ON();
				else
					OLED_OFF();
			}
			if (Key_Scan(KEY4_GPIO_PORT, KEY4_GPIO_PIN) == KEY_ON)
			{
				LedEnable = !LedEnable;
				if(LedEnable)
				{
					TIM_ITConfig(BASIC_TIM,TIM_IT_Update,ENABLE);
				}
				else
				{
					TIM_ITConfig(BASIC_TIM,TIM_IT_Update,DISABLE);
					LED_R_OFF;LED_G_OFF;LED_B_OFF;
				}
			}
		}break;
		default:screenMode = 0;break;
	}
}
/*********************************************END OF FILE**********************/
