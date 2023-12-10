#include "stm32f10x.h" // Device header
#include "InfraredSensor.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "Servo.h"
#include "Serial.h"
#include "PWM.h"
#include "LightSensor.h"
#include "Led.h"
#include "MPU6050.h"
#include <math.h>
#include <stdlib.h>

#define RAD_TO_DEG (180.0 / 3.14)
uint8_t KeyNum;
uint8_t RxData;
uint8_t lsFlag;
uint8_t Flags;
float roll;
float pitch;
uint8_t num1 = 0, num2 = 0, num3 = 0, num4 = 0;
int16_t AX, AY, AZ, GX, GY, GZ;

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
		OLED_ShowString(2, 1, "R FULL");
		Delay_ms(1000);
		OLED_ShowString(2, 1, "                ");
		
	}
	if(num2 >= 5)
	{
		num2 = 0;
		OLED_ShowString(2, 1, "K FULL");
		Delay_ms(1000);
		OLED_ShowString(2, 1, "                ");
		
	}
	if(num3 >= 5)
	{
		num3 = 0;
		OLED_ShowString(2, 1, "H FULL");
		Delay_ms(1000);
		OLED_ShowString(2, 1, "                ");
		
	}
	if(num4 >= 5)
	{
		num4 = 0;
		OLED_ShowString(2, 1, "O FULL");
		Delay_ms(1000);
		OLED_ShowString(2, 1, "                ");
		
	}
}
void Remote_Control(void)
{
	if (Serial_GetRxFlag() == 1)
	{
		RxData = Serial_GetRxData();
		if (RxData == 1)
		{
			
			PWM_Start1();
			num1++;
		}
		
		else if (RxData == 2)
		{
			
			PWM_Start2();
			num2++;
		}
		
		else if (RxData == 3)
		{
			
			PWM_Start3();
			num3++;
		}
		
		else if (RxData == 4)
		{
			
			PWM_Start4();
			num4++;
		}
		else if (RxData == 5)
		{
			LED1_ON();
			Serial_SendString("A 05 05 A");
		}
		else if (RxData == 6)
		{
			LED1_OFF();
			Serial_SendString("A 06 06 A");
		}	
	}
}

void handler(uint8_t flag)
{
	if (flag == 1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
		{
			PWM_SetCompare1(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "Recyclable");
			Serial_SendString("A 01 01 A");
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
			OLED_ShowString(1, 1, "Kitchen");
			Serial_SendString("A 02 02 A");
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
			Serial_SendString("A 03 03 A");
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
			Serial_SendString("A 04 04 A");
			num4++;
		}else
		{
			OLED_ShowString(1, 1, "                ");
			PWM_SetCompare4(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}
	}
}

void LightSensor_check(void)
{
	LightSensor_Init();
	if (LightSensor_Get() == 1 && lsFlag == 1)
	{
		LED1_ON();
		lsFlag = 0;
		Serial_SendString("A 05 05 A");
	}
	else if (LightSensor_Get() == 0 && lsFlag == 0)
	{
		lsFlag = 1;
		LED1_OFF();
		Serial_SendString("A 06 06 A");
	}
}
void Balance_Detection(void)
{
	//角度阈值
	const int tiltThreshold = 30;
	MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
	// 计算倾斜角度
	roll = atan2(AY, AZ) * RAD_TO_DEG; // 滚转角
	pitch = atan2(-AX, sqrt(AY * AY + AZ * AZ)) * RAD_TO_DEG; // 俯仰角
	
	// 判断是否倾斜
	if( roll < 0 )
	{
		roll = -roll;
	}
	if(pitch < 0)
	{
		pitch = -pitch;
	}
  if(roll > tiltThreshold || pitch > tiltThreshold)
	{
		if(Flags == 1)
		{
			OLED_ShowString(2,1,"Falling");
			Serial_SendString("A 07 07 A");
			Flags = 0;
		}
		
		//A0707A
	}else{
		OLED_ShowString(2,1,"Normal ");
		Flags = 1;
	}
}
