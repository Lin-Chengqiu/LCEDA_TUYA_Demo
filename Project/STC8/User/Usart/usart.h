#ifndef _USART_H_
#define _USART_H_

#include "include.h"

#define FOSC            24000000UL
#define BRT             (65536 - FOSC / 115200 / 4)


void UartDebugInit();
void Uart3Init();
void UartDebugSend(uint8_t dat);
void UartDebugSendStr(uint8_t *p);
void Uart3Send(uint8_t dat);
void Uart3SendStr(uint8_t *p);
	
#endif