#ifndef _LED_H_
#define _LED_H_
#include "include.h"
#define LED_R_ON		(P40 = 0)
#define LED_G_ON		(P55 = 0)
#define LED_B_ON		(P54 = 0)

#define LED_R_OFF		(P40 = 1)
#define LED_G_OFF		(P55 = 1)
#define LED_B_OFF		(P54 = 1)

void LED_init(void);
void Flash_Led(void);

#endif