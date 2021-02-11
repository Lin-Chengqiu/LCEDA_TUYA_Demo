#ifndef __DHT11_H
#define	__DHT11_H

#include "include.h"
/************************** DHT11 数据类型定义********************************/
typedef struct
{
	uint8_t  humi_int;		//湿度的整数部分
	uint8_t  humi_deci;	 	//湿度的小数部分
	uint8_t  temp_int;	 	//温度的整数部分
	uint8_t  temp_deci;	 	//温度的小数部分
	uint8_t  check_sum;	 	//校验和
		                 
} DHT11_Data_TypeDef;

/************************** DHT11 函数宏定义********************************/
#define      macDHT11_Dout_0	                            (P17 = 0)
#define      macDHT11_Dout_1	                            (P17 = 1)

#define      macDHT11_Data			                          P17 

/************************** DHT11 函数声明 ********************************/
void                     DHT11_Init                      ( void );
uint8_t                  DHT11_Read_TempAndHumidity      ( DHT11_Data_TypeDef * DHT11_Data );

#endif /* __DHT11_H */







