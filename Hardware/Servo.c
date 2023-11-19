#include "stm32f10x.h" // Device header
#include "PWM.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "InfraredSensor.h"
#include "Serial.h"

void Servo_Init(void)		
{
	PWM_Init();
	OLED_Init();
	Key_Init();
	InfraredSensor_Init();
	Serial_Init();
}
void PWM_Start1(void)
{
	PWM_SetCompare1(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Recyclable");
	Delay_ms(1000);

	PWM_SetCompare1(0 / 180.0 * 2000 + 500);
	OLED_Clear();
	OLED_ShowString(1, 1, "close");
}

void PWM_Start2(void)
{
	PWM_SetCompare2(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Unrecyclable");
	Delay_ms(1000);

	PWM_SetCompare2(0 / 180.0 * 2000 + 500);
	OLED_Clear();
	OLED_ShowString(1, 1, "close");
}

void PWM_Start3(void)
{
	PWM_SetCompare3(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Hazardous");
	Delay_ms(1000);

	PWM_SetCompare3(0 / 180.0 * 2000 + 500);
	OLED_Clear();
	OLED_ShowString(1, 1, "close");
}

void PWM_Start4(void)
{
	PWM_SetCompare4(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Other");
	Delay_ms(1000);

	PWM_SetCompare4(0 / 180.0 * 2000 + 500);
	OLED_Clear();
	OLED_ShowString(1, 1, "close");
}
void Show_SelfInformation(void)
{
	OLED_ShowString(3, 1, "5006210101btz");
	OLED_ShowString(4, 1, "5006210108lfz");
}
void handler(uint8_t flag)
{
	if (flag == 1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 1)
		{
			PWM_SetCompare1(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Unrecyclable");
		}else
		{
			PWM_SetCompare1(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}else if (flag == 2)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 1)
		{
			PWM_SetCompare1(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Unrecyclable");
		}else
		{
			PWM_SetCompare1(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}else if (flag == 3)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 1)
		{
			PWM_SetCompare1(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Hazardous");
		}else
		{
			PWM_SetCompare1(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}else if (flag == 4)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 1)
		{
			PWM_SetCompare1(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Other");
		}else
		{
			PWM_SetCompare1(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}
}
