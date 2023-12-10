#include "stm32f10x.h"                  // Device header
uint8_t LSFlag;
void LightSensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t LightSensor_Get(void)
{
	LSFlag = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15);
	if (LSFlag == 1)
	{
		LSFlag = 0;
		return 1;
	}
	return 0;
}


