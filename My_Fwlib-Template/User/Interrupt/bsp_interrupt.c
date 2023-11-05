#include "bsp_interrupt.h"
// #include "stm32f10x_exti.h"
/** 
  * @brief  ����NVIC 
  * key1        PE3     used to ctrl LED0 
  */
static void My_NVIC_IRQHandler_Init(void)
{
    //����NVIC,�����жϣ�
    NVIC_InitTypeDef My_NVIC_InitStruct;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    My_NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;
    My_NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01u;
    My_NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00u;
    My_NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&My_NVIC_InitStruct);
}
/** 
  * @brief  EXTI Trigger enumeration 
  * key1        PE3     used to ctrl LED0 
  */
void My_EXTI0_IRQHandler_Init(void)
{
    //�����ж��ߣ�
    EXTI_InitTypeDef My_EXTI_InitStruct;
    // GPIOE_Init();
	  // KEY1_ExitLine_Init();/*KEY1  PE3  AFIO ExitLine*/
    //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
    My_EXTI_InitStruct.EXTI_Line = EXTI_Line3;
    My_EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    My_EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    // My_EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&My_EXTI_InitStruct);

    My_NVIC_IRQHandler_Init();
}



