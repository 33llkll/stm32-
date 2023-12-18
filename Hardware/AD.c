#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void AD_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	ADC_InitTypeDef ADC_Initstructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//12Mhz
	
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AIN;	//模拟输入
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Initstructure.ADC_ContinuousConvMode = DISABLE;
	ADC_Initstructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Initstructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_Initstructure.ADC_Mode = ADC_Mode_Independent;
	ADC_Initstructure.ADC_NbrOfChannel = 1;
	ADC_Initstructure.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_Initstructure);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);		//复位校准标志位置一
	while(ADC_GetResetCalibrationStatus(ADC1));		//等待复位校准完成
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);		//读取自动清除标志位
}

uint16_t GetTemperature(void)
{
		uint8_t i;
		uint32_t tempvalue = 0;
		for(i = 0; i < 20; i++)
		{
			tempvalue += AD_GetValue();
			Delay_ms(5);
		}
		return tempvalue/20;
}

uint16_t GetTemp(void)
{
	double AD_Value = (double)GetTemperature()*(3.3/4096.0);
	double Temp = (1.43 - AD_Value)/0.0043+25.0;
	return Temp;
}
