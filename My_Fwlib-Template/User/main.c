/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
// #include "bsp_key.h"
// #include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_interrupt.h"
#include "delay.h"  
#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
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
 * @brief ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
 */
//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(WK_UP==1)	 	 //WK_UP����
	{				 
		BEEP=!BEEP;	
			delay_ms(10);
			LED0=0;
			LED1=0;
			delay_ms(10);
		Gpio_Debug();
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}

void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��



   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	// NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	// NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

  	// NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	// NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

int main(void)
{	
	/* ʹ�ö�Ӧģ��֮ǰ����Ҫ�Ƚ���ģ������ó�ʼ�� */
	delay_init();/* enable delay function */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	// LED_GPIO_Moudle_Init();

	// KEY_GPIO_Init();
	// KEY1_ExitLine_Init();
	// My_EXTI0_IRQHandler_Init();
	// KEY_Init();
	LED_Init();
	BEEP_Init();		 	//��ʼ��������IO
	// EXTIX_Init();
	LED0=0;	
	LED1=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	EXTIX_Init();         	//��ʼ���ⲿ�ж����� 
	LED0=0;					//�ȵ������
	//�����Ե��õĺ�������while(1)��
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
			delay_ms(300); //��ʱ 300ms
			LED0=1;
			LED1=0;
			delay_ms(300); //��ʱ 300ms
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
//  * @brief ǰ4sʹ�ú����˸����־��������������
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
//  * @brief 4s֮�󣬰���ʵ�飻
//  */
// void KEY_Debug_Function(void)
// {//����ʱKEY0ʱ��PE4����͵�ƽ������LED1��������
// 	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)))
// 	{
// 		delay_ms(10);//ȥ����
// 		LED1(1);
// 		delay_ms(10);
// 	}
// 	else
// 	{//δ���£�����
// 		delay_ms(10);//ȥ����
// 		LED1(0);
// 		delay_ms(300);
// 	}
// }

// /**
//  * @brief 4s֮�󣬰���ʵ�飻
//  */
// void KEY0_Debug_Function(void)
// {//����ʱKEY0ʱ��PE4����͵�ƽ������LED1��������
// 	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)))
// 	{
// 		delay_ms(10);//ȥ����
// 		LED0(1);
// 		LED1(1);
// 		delay_ms(10);
// 	}
// 	else
// 	{//δ���£�����
// 		delay_ms(10);//ȥ����
// 		LED0(0);
// 		LED1(0);
// 		delay_ms(300);
// 	}
// }

 /**
 * @brief delay ���������ȵ�ʱ�䣬ע��ʹ�õĳ���
 */
void Delay( uint32_t count )
{
	for(; count!=0; count--);
}

/**
 * @brief My_USART_Send �������ڷ��ͺ���
 */
 void My_USART_Send(USART_TypeDef* USARTx, uint8_t Data)
 {
	USART_SendData(USARTx, Data);
	 //*     @arg USART_FLAG_TXE:  Transmit data register empty flag
	 while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE) == 0)
	 {
		 //ͣ������
	 }
 }

