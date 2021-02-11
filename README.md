# 立创EDA &amp;&amp; 涂鸦智能 第二期物联网实战训练营

This project is developed using Tuya SDK, which enables you to quickly develop branded
apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.

立创EDA：https://oshwhub.com/Just_For_Fun/wu-lian-wang-wen-shi-du-ji

STM32:

```C
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
```

STC8:

```C
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
```

