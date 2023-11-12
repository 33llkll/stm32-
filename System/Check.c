#include "stm32f10x.h"                  // Device header
#include "InfraredSensor.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "Servo.h"

uint8_t Flag;
uint8_t KeyNum;

void Check_main(void)
{
	KeyNum = Key_GetNum();
	Flag = flag_Get();
	if(KeyNum == 1 || Flag == 1)
	{
		PWM_Start();
	}else if(KeyNum == 2 || Flag == 1)
	{
		PWM_Start();
	}else if(KeyNum == 3 || Flag == 1)
	{
		PWM_Start();
	}else if(KeyNum == 4 || Flag == 1)
	{
		PWM_Start();
	}
}
