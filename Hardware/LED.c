#include "stm32f10x.h" // Device header

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_Init(GPIOB, &GPIO_Initstructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_0);
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}
void LED1_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
}
void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_1) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}
void LED2_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	}
}
