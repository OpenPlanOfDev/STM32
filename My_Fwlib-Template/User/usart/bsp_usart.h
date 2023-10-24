#ifndef __BSP_USART_H
#define __BSP_USART_H

#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

#define MY_USART 					USART1
#define MY_USART_CLK 				RCC_APB2Periph_USART1
#define MY_USART_BAUD 				115200
//#define My_USART_Hardware_Flow_Control 0

#define MY_USART_GPIO_CLK   		RCC_APB2Periph_GPIOA
#define MY_USART_GPIO_TX_PORT   	GPIOA
#define MY_USART_GPIO_TX_PIN  	 	GPIO_Pin_9
#define MY_USART_GPIO_RX_PORT  		GPIOA
#define MY_USART_GPIO_RX_PIN  		GPIO_Pin_10

void My_USART_Init(void);

#endif

