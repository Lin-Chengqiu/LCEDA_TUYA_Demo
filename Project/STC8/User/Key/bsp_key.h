#ifndef __KEY_H
#define	__KEY_H


#include "include.h"

sbit KEY1 = P3^7;
sbit KEY2 = P3^6;
 /** 按键按下标置宏
	*  按键按下为高电平，设置 KEY_ON=1， KEY_OFF=0
	*  若按键按下为低电平，把宏设置成KEY_ON=0 ，KEY_OFF=1 即可
	*/
#define KEY_ON	1
#define KEY_OFF	0

void Key_init(void);
void KeyScan(void);

#endif /* __KEY_H */

