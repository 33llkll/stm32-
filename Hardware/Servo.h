#ifndef __SERVO_H
#define __SERVO_H

void Servo_Init(void);	
void PWM_Start1(void);
void PWM_Start2(void);
void PWM_Start3(void);
void PWM_Start4(void);
void Show_SelfInformation(void);
void handler(uint8_t flag);
#endif
