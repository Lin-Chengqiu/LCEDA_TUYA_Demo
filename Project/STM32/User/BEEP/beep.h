#ifndef __BEEP_H
#define __BEEP_H	 
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//蜂鸣器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define BEEP_ON  			GPIO_SetBits(GPIOA,GPIO_Pin_8);
#define BEEP_OFF 			GPIO_ResetBits(GPIOA,GPIO_Pin_8);
void BEEP_Init(void);	//初始化
		 				    
#endif

