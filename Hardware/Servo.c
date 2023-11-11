#include "stm32f10x.h" // Device header
#include "PWM.h"
#include "OLED.h"
#include "Key.h"
#include "Delay.h"
#include "InfraredSensor.h"
uint8_t Keynum;
uint8_t Flag;
uint8_t i;
void Servo_Init(void)
{
	PWM_Init();
	OLED_Init();
	Key_Init();
	InfraredSensor_Init();
	OLED_ShowString(1, 1, "close");
	Keynum = Key_GetNum();
	Flag = flag_Get();
	while(1)
	{
		if(Keynum == 1 || Flag == 1)
		{
			PWM_SetCompare1(90 / 180.0 * 2000 + 500);
			PWM_SetCompare2(90 / 180.0 * 2000 + 500);
			PWM_SetCompare3(90 / 180.0 * 2000 + 500);
			PWM_SetCompare4(90 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "open");
			Delay_ms(1500);
			
			PWM_SetCompare1(0 / 180.0 * 2000 + 500);
			PWM_SetCompare2(0 / 180.0 * 2000 + 500);
			PWM_SetCompare3(0 / 180.0 * 2000 + 500);
			PWM_SetCompare4(0 / 180.0 * 2000 + 500);
			OLED_ShowString(1, 1, "close");
		}	
	}
	
}

		





