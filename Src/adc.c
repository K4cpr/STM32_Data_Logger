/*
 * adc.c
 *
 *  Created on: Apr 19, 2026
 *      Author: kapi-
 */


#include "main.h"
#include "sys_clocks.h"
#include "adc.h"
#include "dma.h"


void Adc_Gpio_Init(void)
{


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

	ADC1->CFGR |= ADC_CFGR_DMAEN;
	ADC1->CFGR |= ADC_CFGR_DMACFG;
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

uint16_t Adc_ReadTest(void)
{
	volatile uint16_t Value;
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
	VoltAdc = AdcResultAvg();
	uint32_t VoltResult = (VoltAdc * 3300)/4095;
	return VoltResult;
}


void AdcDmaStart(void)
{
	ADC1->CFGR |= ADC_CFGR_CONT;
	ADC1->CR |= ADC_CR_ADSTART;
}

uint8_t AdcResult(void)
{

	volatile uint8_t dma_ready = 0;

	if(DMA2->ISR & DMA_ISR_TCIF3)
	{
		dma_ready = 1;
		DMA2->IFCR |= DMA_IFCR_CTCIF3;

	}
	else
	{
		dma_ready = 0;
	}


	return dma_ready;
}

uint16_t AdcResultAvg(void)
{
	uint8_t i;
	uint32_t suma = 0;
	uint16_t Avg = 0;
	if(AdcResult())
	{
		for(i = 0; i<100; i++)
		{
			suma += BuffAdc[i];
		}
		Avg = suma/100;
	}

	return Avg;
}



