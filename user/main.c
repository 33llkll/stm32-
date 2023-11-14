#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Check.h"

int main(void)
{
	Servo_Init();
	OLED_ShowString(1, 1, "close");	
	Show_SelfInformation();
	while (1)
	{
		Check_main();
		Remote_Control();
	}
}
