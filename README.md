# 立创EDA &amp;&amp; 涂鸦智能 第二期物联网实战训练营

This project is developed using Tuya SDK, which enables you to quickly develop branded
apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.

立创EDA：https://oshwhub.com/Just_For_Fun/wu-lian-wang-wen-shi-du-ji

##### 调试流程：

1、获取DHT11的温湿度温湿度数据，并通过串口打印；

2、通过mcu_get_wifi_work_state()获取WBR3工作状态，并通过串口打印WIFI工作状态

3、若WBR3的工作状态为WIFI_CONN_CLOUD，则将温湿度数据上传到涂鸦智能，对比云端数据和本地数据是否一致

4、通过OLED显示温湿度数据及WBR3工作状态

5、通过有源蜂鸣器，提供警报功能，（一开始是想用RGB_LED提供警报功能的，后面就纯粹地将其作为氛围灯）

6、规划按键功能，通过按键实现RGB_LED的关闭与开启、OLED唤醒与休眠、OLED界面切换、更改温湿度警报阈值，并将其写入STM32的FLASH中，可掉电保存、设置wifi工作模式.....

###### STM32:

![image-20210212223853653](https://i.loli.net/2021/02/12/t5yrskc2614XuBe.png)

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

