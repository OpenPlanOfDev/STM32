/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
// #include "bsp_key.h"
// #include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_interrupt.h"
#include "delay.h"  
#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "sys.h"
//#include "usart.h"
#include "my_gpio.h"
/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
// #define MAIN_CHECK_TIME 4000/400
/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/
// static uint8_t Main_Start_Flag = 1;
static uint32_t Key_Debug_Flag = 0;
/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/
// void Main_Debug_Function(void);
// void KEY_Debug_Function(void);//LED0 KEY0 
// void KEY0_Debug_Function(void);//LED1 KEY1 
void My_USART_Send(USART_TypeDef* USARTx, uint8_t Data);
void Gpio_Debug(void);
/*********************************************************************************************************************/
/*----------------------------------------------Function Implementations---------------------------------------------*/
/*********************************************************************************************************************/
/**
 * @brief 来到这里的时候，系统的时钟已经被配置成72M。
 */
//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	if(WK_UP==1)	 	 //WK_UP按键
	{				 
		BEEP=!BEEP;	
			delay_ms(10);
			LED0=0;
			LED1=0;
			delay_ms(10);
		Gpio_Debug();
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}

void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	按键端口初始化

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟



   //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


   //GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	// NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	// NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

  	// NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	// NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

int main(void)
{	
	/* 使用对应模块之前，需要先进行模块的配置初始化 */
	delay_init();/* enable delay function */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// LED_GPIO_Moudle_Init();

	// KEY_GPIO_Init();
	// KEY1_ExitLine_Init();
	// My_EXTI0_IRQHandler_Init();
	// KEY_Init();
	LED_Init();
	BEEP_Init();		 	//初始化蜂鸣器IO
	// EXTIX_Init();
	LED0=0;	
	LED1=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	EXTIX_Init();         	//初始化外部中断输入 
	LED0=0;					//先点亮红灯
	//周期性调用的函数放在while(1)中
	while(1)
	{
		Gpio_Debug();
		// printf("OK\r\n");	
		delay_ms(100);	
		// Main_Debug_Function();
		My_USART_Send(MY_USART,'OK');
	}
}
void Gpio_Debug(void)
{
	for (Key_Debug_Flag = 0; Key_Debug_Flag < 10000; Key_Debug_Flag++ )
	{
		Key_Debug_Flag++;
		if(Key_Debug_Flag<= 20)
		{
			LED0=0;
			LED1=1;
			delay_ms(300); //延时 300ms
			LED0=1;
			LED1=0;
			delay_ms(300); //延时 300ms
		}
		else if((Key_Debug_Flag > 20) && (Key_Debug_Flag<= 24))
		{
			{
			BEEP=1;
			delay_ms(50);
			BEEP=0;
			delay_ms(10);
			LED0=0;
			LED1=0;
			}
		}
		else
		{
			// if(WK_UP)
			// {
			// 	delay_ms(100);
			// 	BEEP=0;
			// 	delay_ms(100);
			// }
			// else
			// {
			// 	BEEP=0;
			// 	delay_ms(10);
			// 	// BEEP=1;
			// 	delay_ms(10);
			// 	if(KEY1)
			// 	{
			// 		BEEP=0;
			// 		delay_ms(10);
			// 		LED1=1;
			// 		delay_ms(500);
			// 	}
			// 	else
			// 	{
			// 		delay_ms(10);
			// 		LED1=0;
			// 		delay_ms(500);
					if(KEY0)
					{
						BEEP=1;
						delay_ms(10);
						LED0=0;
						delay_ms(100);
					}
					else
					{
						BEEP=0;
						delay_ms(10);
						LED0=1;
						LED1=0;
						delay_ms(100);
					}
		// 		}
		// 	}
		}
	}
}
// /**
//  * @brief 前4s使用红灯闪烁，标志程序运行正常；
//  */
// void Main_Debug_Function(void)
// {
// 	uint8_t Run_Cnt = 0;
// 	if(Main_Start_Flag == 1)
// 	{
// 		for (Run_Cnt = MAIN_CHECK_TIME; Run_Cnt > 0; Run_Cnt-- )
// 		{
// 			LED0(1);
// 			delay_ms(200);
// 			LED0(0);
// 			delay_ms(200);
// 			if(Run_Cnt == 1)
// 			{
// 				Main_Start_Flag = 0;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		Main_Start_Flag = 0;
// 	}
// }
// /**
//  * @brief 4s之后，按键实验；
//  */
// void KEY_Debug_Function(void)
// {//按下时KEY0时，PE4输出低电平，开启LED1；灯亮；
// 	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)))
// 	{
// 		delay_ms(10);//去抖动
// 		LED1(1);
// 		delay_ms(10);
// 	}
// 	else
// 	{//未按下，灯灭
// 		delay_ms(10);//去抖动
// 		LED1(0);
// 		delay_ms(300);
// 	}
// }

// /**
//  * @brief 4s之后，按键实验；
//  */
// void KEY0_Debug_Function(void)
// {//按下时KEY0时，PE4输出低电平，开启LED1；灯亮；
// 	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)))
// 	{
// 		delay_ms(10);//去抖动
// 		LED0(1);
// 		LED1(1);
// 		delay_ms(10);
// 	}
// 	else
// 	{//未按下，灯灭
// 		delay_ms(10);//去抖动
// 		LED0(0);
// 		LED1(0);
// 		delay_ms(300);
// 	}
// }

 /**
 * @brief delay 函数是死等的时间，注意使用的场合
 */
void Delay( uint32_t count )
{
	for(; count!=0; count--);
}

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

