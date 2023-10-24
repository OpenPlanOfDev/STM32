#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
/*KEY0  PE4*/
#define KEY0_GPIOE_PIN4                  GPIO_Pin_4
#define KEY0_GPIO_PORT                   GPIOE
#define KEY0_GPIOE_CLK                   RCC_APB2Periph_GPIOE

/*KEY1  PE3*/
#define KEY1_GPIOE_PIN3                  GPIO_Pin_3
#define KEY1_GPIO_PORT                   GPIOE
#define KEY1_GPIOE_CLK                   RCC_APB2Periph_GPIOE

/*KEY1  PE3  EXITLine  AFIO*/
#define KEY1_EXITLine_PIN                GPIO_PinSource3
#define KEY1_EXITLine_PORT               GPIO_PortSourceGPIOE
#define KEY1_EXITLine_CLK                RCC_APB2Periph_AFIO


void KEY_GPIO_Init(void);

#endif /* __BSP_KEY_H */


