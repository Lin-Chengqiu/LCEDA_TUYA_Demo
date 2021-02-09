/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./Led/bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
	
//打开时钟函数
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);	//打开GPIO口时钟，先打开复用才能修改复用功能
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//要先开时钟，再重映射；这句表示关闭jtag，使能swd。  
//如果是HAL库，使用 __HAL_AFIO_REMAP_SWJ_NOJTAG();              //禁用JTAG
	
	
		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	
			/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
		
    		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = LED_R_GPIO_PIN;
		GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = LED_G_GPIO_PIN;
		GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure);		
		GPIO_InitStructure.GPIO_Pin = LED_B_GPIO_PIN;
		GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStructure);		
		/* 关闭所有led灯	*/
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
		
		/* 关闭所有led灯	*/
		GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);	 
    
    		/* 关闭所有led灯	*/
		GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);	 
		
			GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);	 
			GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);	 
			GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);	 
}

/**
  * @brief  流水灯函数
  *	@note   每调用一次，就改变一次LED状态
  * @param  无
  * @retval 无
  */
void Flash_Led(void)
{
	static u8 count = 0;     //LED标志位
	switch(++count)
	{
		case 1: LED_R_ON;LED_G_OFF;LED_B_OFF;break;//点亮LED1
		case 2: LED_R_OFF;LED_G_ON;LED_B_OFF;break;//点亮LED2s
		default :LED_R_OFF;LED_G_OFF;LED_B_ON;count = 0; break;
	}
}

/*********************************************END OF FILE**********************/
