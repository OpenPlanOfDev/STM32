#include "bsp_usart.h"



static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

void My_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//ʹ�� RX �� TX ���� GPIO ʱ�Ӻ� USART ʱ�ӣ�
	RCC_APB2PeriphClockCmd(MY_USART_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//��ʼ�� GPIO������ GPIO ���õ� USART �ϣ�
	{
		//TX--���
		GPIO_InitStructure.GPIO_Pin = MY_USART_GPIO_TX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(MY_USART_GPIO_TX_PORT, &GPIO_InitStructure);
	}

	{
		//RX--����
		GPIO_InitStructure.GPIO_Pin = MY_USART_GPIO_RX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(MY_USART_GPIO_RX_PORT, &GPIO_InitStructure);
	}
	
	//���� USART ������
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
	//ʹ���ж�
	USART_ITConfig(MY_USART, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(MY_USART, ENABLE);
}



 