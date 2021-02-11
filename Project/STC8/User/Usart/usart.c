#include "./Usart/usart.h"

bit busy_debug;
uint8_t wptr1;
uint8_t rptr1;
uint8_t buffer1[16];

bit busy;
uint8_t wptr;
uint8_t rptr;
uint8_t buffer[16];

void UartDebugIsr() interrupt 4
{
    if (TI)
    {
        TI = 0;
        busy_debug = 0;
    }
    if (RI)
    {
        RI = 0;
        buffer1[wptr1++] = SBUF;
        wptr1 &= 0x0f;
    }
}

void Uart3Isr() interrupt 17
{
    if (S3CON & 0x02)
    {
        S3CON &= ~0x02;
        busy = 0;
    }
    if (S3CON & 0x01)
    {
        S3CON &= ~0x01;
//        buffer[wptr++] = S3BUF;
//        wptr &= 0x0f;
			uart_receive_input(S3BUF);
    }
}

void UartDebugInit()
{
	  SCON = 0x50;
    TMOD |= 0x00;
    TL1 = BRT;
    TH1 = BRT >> 8;
    TR1 = 1;
    AUXR = 0x40;
    wptr1 = 0x00;
    rptr1 = 0x00;
    busy_debug = 0;
	  ES = 1;
    EA = 1;
}

void Uart3Init()
{
    S3CON = 0x10;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR |= 0x14;
    wptr = 0x00;
    rptr = 0x00;
    busy = 0;
    IE2|=ES3;
    EA = 1;
}

void UartDebugSend(uint8_t dat)
{
    while (busy_debug);
    busy_debug = 1;
    SBUF = dat;
}

void UartDebugSendStr(uint8_t *p)
{
    while (*p)
    {
        UartDebugSend(*p++);
    }
}

void Uart3Send(uint8_t dat)
{
    while (busy);
    busy = 1;
    S3BUF = dat;
}

void Uart3SendStr(uint8_t *p)
{
    while (*p)
    {
        Uart3Send(*p++);
    }
}

