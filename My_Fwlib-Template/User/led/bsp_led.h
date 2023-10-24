#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
/*LED0  PB5*/
#define LED0_GPIOB_PIN5                  GPIO_Pin_5
#define LED0_GPIO_PORT                   GPIOB
#define LED0_GPIOB_CLK                   RCC_APB2Periph_GPIOB

/*LED1  PE5*/
#define LED1_GPIOE_PIN5                  GPIO_Pin_5
#define LED1_GPIO_PORT                   GPIOE
#define LED1_GPIOE_CLK                   RCC_APB2Periph_GPIOE

/* used Micro to implying state, be good at understanding */
#define    ON        1
#define    OFF       0

// \  C语言里面叫续行符，后面不能有任何的东西

#define   LED0(state)   if(state) \
	                          GPIO_ResetBits(LED0_GPIO_PORT, LED0_GPIOB_PIN5); \
                        else  GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIOB_PIN5);
#define   LED1(state)   if(state) \
	                          GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIOE_PIN5); \
                        else  GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIOE_PIN5);

void LED_GPIO_Moudle_Init(void);

#endif /* __BSP_LED_H */

