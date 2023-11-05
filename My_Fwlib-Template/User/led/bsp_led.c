// bsp ：board support package 板级支持包
#include "bsp_led.h"

void GPIOB_Init(void);
void GPIOE_Init(void);

void LED_GPIO_Moudle_Init(void)
{
	GPIOB_Init();/*LED0  PB5*/
	GPIOE_Init();/*LED1  PE5*/
}

void GPIOB_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED0_GPIOB_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED0_GPIOB_PIN5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);
	GPIO_SetBits(LED0_GPIO_PORT, LED0_GPIOB_PIN5);//默认灯灭
}
void GPIOE_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	// RCC_APB2PeriphClockCmd(LED0_GPIOB_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(LED1_GPIOE_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED1_GPIOE_PIN5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIOE_PIN5);//默认灯灭
}

