/**
 * @file bsp_key.c
 * @author your name (you@domain.com)
 * @brief 
 *       通常按键检测需要进行消抖处理；
 * @version 0.1
 * @date 2023-10-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "bsp_key.h"

void KEY0_Init(void);
void KEY1_Init(void);
void KEY1_ExitLine_Init(void);

void KEY_GPIO_Init(void)
{
	KEY0_Init();/*KEY0  PE4*/
	KEY1_Init();/*KEY1  PE3*/
	// KEY1_ExitLine_Init();
	// GPIOE_Init();/*LED1  PE5*/
}

void KEY0_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY0_GPIOE_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = KEY0_GPIOE_PIN4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//先配置成输入上拉模式
	
	GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);
}

void KEY1_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY1_GPIOE_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIOE_PIN3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//先配置成输入上拉模式
	
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
}

void KEY1_ExitLine_Init(void)
{
	RCC_APB2PeriphClockCmd(KEY1_EXITLine_CLK, ENABLE);//使能复用功能时钟
	GPIO_EXTILineConfig(KEY1_EXITLine_PORT, KEY1_EXITLine_PIN);
}

// void EXTI3_IRQHandler(void)
// {
// 	delay_ms(100);//消抖
// 	if(KEY1 == 1)	 //按键KEY1
// 	{				 
// 		LED0(1);
// 	}		 
// 	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
// }


