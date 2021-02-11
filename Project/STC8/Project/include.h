#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <STC8.H>
#include <intrins.h>

typedef unsigned char 	uint8_t;
typedef unsigned int 		uint16_t;
typedef unsigned long		uint32_t;

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;

#include "./Usart/usart.h"
#include "./LED/LED.h"
#include "./Timer/Timer.h"
#include "./OLED/OLED_I2C.h"
#include "./dht11/bsp_dht11.h"
#include "wifi.h"
#include "./delay/delay.h"
#include "./key/bsp_key.h"  

#endif