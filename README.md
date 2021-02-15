# 立创EDA &amp;&amp; 涂鸦智能 第二期物联网实战训练营

This project is developed using Tuya SDK, which enables you to quickly develop branded
apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.

之前用过ESP8266将数据上传到OneNET，对比之下涂鸦模组更易于上手使用，而且涂鸦智能提供了MCU_SDK，能够让我们快速地完成 MCU 程序开发

立创EDA：https://oshwhub.com/Just_For_Fun/wu-lian-wang-wen-shi-du-ji

##### 调试流程：

1、通过DHT11的获取温湿度数据，并通过串口打印；

2、通过mcu_get_wifi_work_state()获取WBR3工作状态，并通过串口打印WIFI工作状态

3、若WBR3的工作状态为WIFI_CONN_CLOUD，则将温湿度数据上传到涂鸦智能，对比云端数据和本地数据是否一致

4、通过OLED显示温湿度数据及WBR3工作状态

5、通过有源蜂鸣器，提供警报功能，（一开始是想用RGB_LED提供警报功能的，后面就纯粹地将其作为氛围灯）

6、规划按键功能，通过按键实现RGB_LED的关闭与开启、OLED唤醒与休眠、OLED界面切换、更改温湿度警报阈值，并将其写入STM32的FLASH中，可掉电保存、设置wifi工作模式.....

###### STM32:

![image-20210212223853653](https://i.loli.net/2021/02/12/t5yrskc2614XuBe.png)

初次连接设备需要进行配网

![IMG_20210213_211150](https://i.loli.net/2021/02/14/vmPTyQVSiROxXqc.jpg)![IMG_20210213_211128](https://i.loli.net/2021/02/14/UpMz7cFXyOlbhES.jpg)

此时APP上可以发现可用设备

![Screenshot_20210213-211047](https://i.loli.net/2021/02/14/WTa6gsxlDBfvO8Y.jpg)![Screenshot_20210214-214918](https://i.loli.net/2021/02/14/XStxhW24GiwYg1I.jpg)![Screenshot_20210214-215005](https://i.loli.net/2021/02/14/5lwvF6OdH7R8gmW.jpg)


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

我是先写的STM32的代码，然后直接移植STM32的部分代码到STC8上，实际上并没有太大区别

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

