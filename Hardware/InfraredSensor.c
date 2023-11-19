#include "stm32f10x.h"                  // Device header
#include "Servo.h"
uint8_t flag;
void InfraredSensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line7 | EXTI_Line5 | EXTI_Line6 | EXTI_Line8;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //响应
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI9_5_IRQHandler(void)                                                                                                                                                                       
{
	if (EXTI_GetITStatus(EXTI_Line5) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
		{
			flag = 1;
		}
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	
	else if (EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
		{
			flag = 2;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	
	else if (EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0)
		{
			flag = 3;
		}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	
	else if (EXTI_GetITStatus(EXTI_Line8) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
		{
			flag = 4;
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	handler(flag);
}
