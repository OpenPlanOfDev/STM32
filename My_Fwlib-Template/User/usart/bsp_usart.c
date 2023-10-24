#include "bsp_usart.h"



static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

void My_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//使能 RX 和 TX 引脚 GPIO 时钟和 USART 时钟；
	RCC_APB2PeriphClockCmd(MY_USART_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//初始化 GPIO，并将 GPIO 复用到 USART 上；
	{
		//TX--输出
		GPIO_InitStructure.GPIO_Pin = MY_USART_GPIO_TX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(MY_USART_GPIO_TX_PORT, &GPIO_InitStructure);
	}

	{
		//RX--输入
		GPIO_InitStructure.GPIO_Pin = MY_USART_GPIO_RX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(MY_USART_GPIO_RX_PORT, &GPIO_InitStructure);
	}
	
	//配置 USART 参数；
	{
		USART_InitStructure.USART_BaudRate = MY_USART_BAUD;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_Init(MY_USART, &USART_InitStructure);
	}
	NVIC_Configuration();
	//使能中断
	USART_ITConfig(MY_USART, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(MY_USART, ENABLE);
}



 