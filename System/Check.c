#include "stm32f10x.h" // Device header
#include "InfraredSensor.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "Servo.h"
#include "Serial.h"

uint8_t Flag;
uint8_t KeyNum;
uint8_t RxData;

void Check_main(void)
{
	KeyNum = Key_GetNum();
	Flag = flag_Get();
	if (KeyNum == 1 || Flag == 1)
	{
		PWM_Start1();
	}
	else if (KeyNum == 2 || Flag == 1)
	{
		PWM_Start2();
	}
	else if (KeyNum == 3 || Flag == 1)
	{
		PWM_Start3();
	}
	else if (KeyNum == 4 || Flag == 1)
	{
		PWM_Start4();
	}
}
void Remote_Control(void)
{
	RxData = Serial_GetRxData();
	if (RxData == 1)
	{
		PWM_Start1();
	}
	else if (RxData == 2)
	{
		PWM_Start2();
	}
	else if (RxData == 3)
	{
		PWM_Start3();
	}
	else if (RxData == 4)
	{
		PWM_Start4();
	}

}
