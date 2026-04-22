/*
 * adc.c
 *
 *  Created on: Apr 19, 2026
 *      Author: kapi-
 */


#include "main.h"
#include "sys_clocks.h"



void Adc_Gpio_Init(void)
{
	//PA0 ADC 12 IN5
	//edit PC2 ADC123_INP3
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

	GPIOC->MODER &= ~(GPIO_MODER_MODE2);
	GPIOC->MODER |= GPIO_MODER_MODE2;

	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD2);

}

void Adc_Config(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

	ADC1->CR &= ~(ADC_CR_DEEPPWD);

	ADC1->CR &= ~(ADC_CR_ADVREGEN);
	ADC1->CR |= ADC_CR_ADVREGEN;

	for(volatile uint32_t i = 0; i < 1000; i++)
	{
		__NOP();
	}

	ADC1->CR &= ~(ADC_CR_ADEN);

	ADC1->CR &= ~(ADC_CR_ADCALDIF);

	ADC1->CR &= ~(ADC_CR_ADCAL);
	ADC1->CR |= ADC_CR_ADCAL;
	while(ADC1->CR & ADC_CR_ADCAL){}
}

void Adc_Init(void)
{
	Adc_Gpio_Init();
	Adc_Config();

	ADC1->CR |= ADC_CR_ADEN;

	while(!(ADC1->ISR & ADC_ISR_ADRDY)){}

	ADC1->SQR1 &= ~ADC_SQR1_SQ1_Msk;

	ADC1->SQR1 |= (0x03UL << ADC_SQR1_SQ1_Pos);
	ADC1->SMPR1 |= ((ADC_SMPR1_SMP5_0) | (ADC_SMPR1_SMP5_2));

}

uint32_t Adc_Read(void)
{
	uint32_t Value;
	ADC1->CR |= ADC_CR_ADSTART;
	while(!(ADC1->ISR & ADC_ISR_EOC))
	{

	}

	Value = ADC1->DR;
	return Value;
}

uint32_t Adc_Volt_Read(void)
{
	uint32_t VoltAdc;
	VoltAdc = Adc_Read();
	uint32_t VoltResult = (VoltAdc * 3300)/4095;
	return VoltResult;
}










