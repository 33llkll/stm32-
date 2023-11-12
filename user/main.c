#include "stm32f10x.h" // Device header
#include "InfraredSensor.h"
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "Check.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Servo_Init();
	OLED_ShowString(1, 1, "close");
	while (1)
	{
		Check_main();          
	}
}
