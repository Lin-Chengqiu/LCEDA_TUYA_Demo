# 立创EDA &amp;&amp; 涂鸦智能 第二期物联网实战训练营

This project is developed using Tuya SDK, which enables you to quickly develop branded
apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.

立创EDA：https://oshwhub.com/Just_For_Fun/wu-lian-wang-wen-shi-du-

普普通通，没有什么特点

###### STM32:

![image-20210212223853653](https://i.loli.net/2021/02/13/4lRVdWpkLs6MouB.png)

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

###### STC8:

直接移植STM32的部分代码

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

