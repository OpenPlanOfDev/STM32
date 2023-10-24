/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_interrupt.h"
#include "delay.h"  
#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
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
 
 /**
 * @brief delay ���������ȵ�ʱ�䣬ע��ʹ�õĳ���
 */
void Delay( uint32_t count )
{
	for(; count!=0; count--);
}

/**
 * @brief ���������ʱ��ϵͳ��ʱ���Ѿ������ó�72M��
 */
int main(void)
{	
	/* ʹ�ö�Ӧģ��֮ǰ����Ҫ�Ƚ���ģ������ó�ʼ�� */
	delay_init();/* enable delay function */
	LED_GPIO_Moudle_Init();
	KEY_GPIO_Init();
	
	My_USART_Init();
	My_EXTI0_IRQHandler_Init();
	//�����Ե��õĺ�������while(1)��
	while(1)
	{
		Main_Debug_Function();
		if(Main_Start_Flag == 0)
		{//4s���ʱ��֮�󣬿��Խ��а������ܲ���:KEY0 LED1
			KEY_Debug_Function();
			// KEY0_Debug_Function();
		}
		else{	;	}
		My_USART_Send(MY_USART,'A');
		
	}
}
/**
 * @brief ǰ4sʹ�ú����˸����־��������������
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
 * @brief 4s֮�󣬰���ʵ�飻
 */
void KEY_Debug_Function(void)
{//����ʱKEY0ʱ��PE4����͵�ƽ������LED1��������
	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)))
	{
		delay_ms(10);//ȥ����
		LED1(1);
		delay_ms(10);
	}
	else
	{//δ���£�����
		delay_ms(10);//ȥ����
		LED1(0);
		delay_ms(300);
	}
}

/**
 * @brief 4s֮�󣬰���ʵ�飻
 */
void KEY0_Debug_Function(void)
{//����ʱKEY0ʱ��PE4����͵�ƽ������LED1��������
	if(!(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)))
	{
		delay_ms(10);//ȥ����
		LED0(0);
		delay_ms(10);
	}
	else
	{//δ���£�����
		delay_ms(10);//ȥ����
		LED0(1);
		delay_ms(300);
	}
}

