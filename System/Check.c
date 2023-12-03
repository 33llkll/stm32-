#include "stm32f10x.h" // Device header
#include "InfraredSensor.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "Servo.h"
#include "Serial.h"
#include "PWM.h"
#include "string.h"

uint8_t KeyNum;
uint8_t RxData;

uint8_t num1 = 0, num2 = 0, num3 = 0, num4 = 0;

void Check_main(void)
{
	KeyNum = Key_GetNum();
	
	if (KeyNum == 1)
	{
		PWM_Start1();
		num1++;
	}
	else if (KeyNum == 2)
	{
		PWM_Start2();
		num2++;
	}
	else if (KeyNum == 3)
	{
		PWM_Start3();
		num3++;
	}
	else if (KeyNum == 4)
	{
		PWM_Start4();
		num4++;
	}
	
	if(num1 >= 5)
	{
		num1 = 0;
		OLED_ShowString(2, 1, "FULL");
		Delay_ms(500);
		OLED_ShowString(2, 1, "                ");
		
	}
	if(num2 >= 5)
	{
		num2 = 0;
		OLED_ShowString(2, 1, "FULL");
		Delay_ms(500);
		OLED_ShowString(2, 1, "                ");
		
	}
	if(num3 >= 5)
	{
		num3 = 0;
		OLED_ShowString(2, 1, "FULL");
		Delay_ms(500);
		OLED_ShowString(2, 1, "                ");
		
	}
	if(num4 >= 5)
	{
		num4 = 0;
		OLED_ShowString(2, 1, "FULL");
		Delay_ms(500);
		OLED_ShowString(2, 1, "                ");
		
	}
}
void Remote_Control(void)
{
	if (Serial_RxFlag == 1)
	{
		if (strcmp(Serial_RxPacket, "Recyclable") == 0)
		{
			Serial_SendString("Recyclable");
			PWM_Start1();
			num1++;
		}
		
		else if (strcmp(Serial_RxPacket, "Unrecyclable") == 0)
		{
			Serial_SendString("Unrecyclable");
			PWM_Start2();
			num2++;
		}
		
		else if (strcmp(Serial_RxPacket, "Hazardous") == 0)
		{
			Serial_SendString("Hazardous");
			PWM_Start3();
			num3++;
		}
		
		else if (strcmp(Serial_RxPacket, "Other") == 0)
		{
			Serial_SendString("Other");
			PWM_Start4();
			num4++;
		}
			
	}
	Serial_RxFlag = 0;
}

void handler(uint8_t flag)
{
	if (flag == 1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
		{
			PWM_SetCompare1(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Recyclable");
			Serial_SendString("Recyclable");
			num1++;
		}else
		{
			OLED_ShowString(1, 1, "                ");
			PWM_SetCompare1(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}else if (flag == 2)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
		{
			PWM_SetCompare2(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Unrecyclable");
			Serial_SendString("Unrecyclable");
			num2++;
		}else
		{
			OLED_ShowString(1, 1, "                ");
			PWM_SetCompare2(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}else if (flag == 3)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0)
		{
			PWM_SetCompare3(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Hazardous");
			Serial_SendString("Hazardous");
			num3++;
		}else
		{
			OLED_ShowString(1, 1, "                ");
			PWM_SetCompare3(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}else if (flag == 4)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0)
		{
			PWM_SetCompare4(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Other");
			Serial_SendString("Other");
			num4++;
		}else
		{
			OLED_ShowString(1, 1, "                ");
			PWM_SetCompare4(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}
}
