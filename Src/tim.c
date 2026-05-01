/*
 * tim.c
 *
 *  Created on: Apr 29, 2026
 *      Author: kapi-
 */

#include "main.h"
#include "sys_clocks.h"
#include "tim.h"

volatile uint16_t num = 0;
volatile uint16_t minute = 0;


void Tim6Init(void)
{
	RCC->APB1ENR1 &= ~(RCC_APB1ENR1_TIM6EN);
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
	while(!(RCC->APB1ENR1 & RCC_APB1ENR1_TIM6EN));

	TIM6->CNT = 0;
}

void Tim6Start(void)
{
	TIM6->PSC = 47;
	TIM6->ARR = 9999;
	TIM6->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM6_DAC_IRQn, 2);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	TIM6->CR1 |= TIM_CR1_CEN;
}

void TIM6_DACUNDER_IRQHandler(void)
{
	if(TIM6->SR & TIM_SR_UIF)
	{
		TIM6->SR &= ~(TIM_SR_UIF);
		num++;
		if(num == 6000)
		{
			num = 0;
			minute = 1;
		}
	}

}
