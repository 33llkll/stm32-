#include "stm32f10x.h" // Device header
#include "PWM.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "InfraredSensor.h"
#include "Serial.h"
#include "LED.h"
#include "MPU6050.h"
void Servo_Init(void)		
{
	PWM_Init();
	OLED_Init();
	Key_Init();
	InfraredSensor_Init();
	Serial_Init();
	LED_Init();
	MPU6050_Init();
}
void PWM_Start1(void)
{
	Serial_SendString("A 01 01 A");
	PWM_SetCompare1(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Recyclable");
	Delay_ms(1000);

	PWM_SetCompare1(0 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "                ");
	OLED_ShowString(1, 1, "close");
}

void PWM_Start2(void)
{
	Serial_SendString("A 02 02 A");
	PWM_SetCompare2(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Kitchen");
	
	Delay_ms(1000);

	PWM_SetCompare2(0 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "                ");
	OLED_ShowString(1, 1, "close");
}

void PWM_Start3(void)
{
	Serial_SendString("A 03 03 A");
	PWM_SetCompare3(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Hazardous");
	
	Delay_ms(1000);

	PWM_SetCompare3(0 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "                ");
	OLED_ShowString(1, 1, "close");
}

void PWM_Start4(void)
{
	Serial_SendString("A 04 04 A");
	PWM_SetCompare4(90 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "Other");
	
	Delay_ms(1000);

	PWM_SetCompare4(0 / 180.0 * 2000 + 500);
	OLED_ShowString(1, 1, "                ");
	OLED_ShowString(1, 1, "close");
}
void Show_SelfInformation(void)
{
	OLED_ShowString(3, 1, "5006210101btz");
	OLED_ShowString(4, 1, "5006210108lfz");
}
