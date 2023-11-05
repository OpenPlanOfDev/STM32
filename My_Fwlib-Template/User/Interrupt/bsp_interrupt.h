#ifndef __BSP_INTERRUPT_H
#define __BSP_INTERRUPT_H
/*
1-头文件包含建议按照字母顺序书写，其他的宏、变量、函数等声明建议按照功能模块存放；
2-仅被本文件使用的变量或者函数，建议使用“static”限定；
*/
/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "bsp_key.h"
#include "bsp_led.h"
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define XXX_counter 0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 
//蜂鸣器端口定义
#define BEEP PBout(8)	// BEEP,蜂鸣器接口		   


/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
static uint8_t XXXX_Flag = 1;
/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void My_EXTI0_IRQHandler_Init(void);

extern void KEY1_ExitLine_Init(void);
/*********************************************************************************************************************/
/*----------------------------------------------Function Implementations---------------------------------------------*/
/*********************************************************************************************************************/
#endif
/* __BSP_INTERRUPT_H */

