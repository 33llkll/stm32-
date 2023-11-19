#include "stm32f10x.h" // Device header
#include "InfraredSensor.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "Servo.h"
#include "Serial.h"

uint8_t KeyNum;
uint8_t RxData;
uint8_t fflag;

void Check_main(void)
{
	KeyNum = Key_GetNum();
	if (KeyNum == 1)
	{
		PWM_Start1();
	}
	else if (KeyNum == 2)
	{
		PWM_Start2();
	}
	else if (KeyNum == 3)
	{
		PWM_Start3();
	}
	else if (KeyNum == 4)
	{
		PWM_Start4();
	}
}
void Remote_Control(void)
{
	RxData = Serial_GetRxData();
	if (fflag == RxData)
	{
		return;
	}
	else
	{
		fflag = RxData;
	}
	if (fflag == 1)
	{
		PWM_Start1();
	}
	else if (fflag == 2)
	{
		PWM_Start2();
	}
	else if (fflag == 3)
	{
		PWM_Start3();
	}
	else if (fflag == 4)
	{
		PWM_Start4();
	}
}
