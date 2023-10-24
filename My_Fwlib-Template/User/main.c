/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_interrupt.h"
#include "delay.h"  
#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "sys.h"
//#include "usart.h"


/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define MAIN_CHECK_TIME 4000/400
/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
static uint8_t Main_Start_Flag = 1;
/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
void Main_Debug_Function(void);
void KEY_Debug_Function(void);//LED0 KEY0 
void KEY0_Debug_Function(void);//LED1 KEY1 
/*********************************************************************************************************************/
/*----------------------------------------------Function Implementations---------------------------------------------*/
/*********************************************************************************************************************/

/**
 * @brief My_USART_Send 函数串口发送函数
 */
 void My_USART_Send(USART_TypeDef* USARTx, uint8_t Data)
 {
	USART_SendData(USARTx, Data);
	 //*     @arg USART_FLAG_TXE:  Transmit data register empty flag
	 while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == 0)
	 {
		 //停在这里
	 }
 }
 
 /**
 * @brief delay 函数是死等的时间，注意使用的场合
 */
void Delay( uint32_t count )
{
	for(; count!=0; count--);
}

/**
 * @brief 来到这里的时候，系统的时钟已经被配置成72M。
 */
int main(void)
{	
	/* 使用对应模块之前，需要先进行模块的配置初始化 */
	delay_init();/* enable delay function */
	LED_GPIO_Moudle_Init();
	KEY_GPIO_Init();
	
	My_USART_Init();
	My_EXTI0_IRQHandler_Init();
	//周期性调用的函数放在while(1)中
	while(1)
	{
		Main_Debug_Function();
		if(Main_Start_Flag == 0)
		{//4s检测时间之后，可以进行按键功能测试:KEY0 LED1
			KEY_Debug_Function();
			// KEY0_Debug_Function();
		}
		else{	;	}
		My_USART_Send(MY_USART,'A');
		
	}
}
/**
 * @brief 前4s使用红灯闪烁，标志程序运行正常；
 */
void Main_Debug_Function(void)
{
	uint8_t Run_Cnt = 0;
	if(Main_Start_Flag == 1)
	{
		for (Run_Cnt = MAIN_CHECK_TIME; Run_Cnt > 0; Run_Cnt-- )
		{
			LED0(1);
			delay_ms(200);
			LED0(0);
			delay_ms(200);
			if(Run_Cnt == 1)
			{
				Main_Start_Flag = 0;
			}
		}
	}
	else
	{
		Main_Start_Flag = 0;
	}
}
/**
 * @brief 4s之后，按键实验；
 */
void KEY_Debug_Function(void)
{//按下时KEY0时，PE4输出低电平，开启LED1；灯亮；
	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)))
	{
		delay_ms(10);//去抖动
		LED1(1);
		delay_ms(10);
	}
	else
	{//未按下，灯灭
		delay_ms(10);//去抖动
		LED1(0);
		delay_ms(300);
	}
}

/**
 * @brief 4s之后，按键实验；
 */
void KEY0_Debug_Function(void)
{//按下时KEY0时，PE4输出低电平，开启LED1；灯亮；
	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)))
	{
		delay_ms(10);//去抖动
		LED0(0);
		delay_ms(10);
	}
	else
	{//未按下，灯灭
		delay_ms(10);//去抖动
		LED0(1);
		delay_ms(300);
	}
}

