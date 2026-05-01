/*
 * dma.c
 *
 *  Created on: Apr 29, 2026
 *      Author: kapi-
 */

#include "dma.h"
#include "main.h"
#include "sys_clocks.h"
#include "adc.h"
#include "lpuart.h"


volatile uint16_t BuffAdc[100];

void Dma2AdcInit(void)
{
	//dma2 channel 3 FOR ADC
	DMA2_Channel3->CCR &= ~(DMA_CCR_EN);
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	DMA2_Channel3->CCR |= DMA_CCR_MSIZE_0;
	DMA2_Channel3->CCR |= DMA_CCR_PSIZE_0;
	DMA2_Channel3->CCR |= DMA_CCR_MINC;
	DMA2_Channel3->CCR |= DMA_CCR_PL_1;
	DMA2_Channel3->CCR |= DMA_CCR_CIRC;

}

void Dma2AdcStart(void)
{
	DMA2_Channel3->CPAR = (uint32_t)&ADC1->DR; //
	DMA2_Channel3->CMAR = (uint32_t)&BuffAdc[0]; //

	DMA2_Channel3->CNDTR = 100; //
	DMA2_Channel3->CCR |= DMA_CCR_EN;
}



void Dma2UartInit(void)
{
	//dma2 channel 6 FOR UART
	DMA2_Channel6->CCR &= ~(DMA_CCR_EN);
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

	DMA2_Channel6->CCR &= ~(DMA_CCR_MSIZE);
	DMA2_Channel6->CCR &= ~(DMA_CCR_PSIZE);

	DMA2_CSELR->CSELR &= ~DMA_CSELR_C6S;
	DMA2_CSELR->CSELR |=  (0x4 << DMA_CSELR_C6S_Pos);

	DMA2_Channel6->CCR |= DMA_CCR_MINC;
	DMA2_Channel6->CCR |= DMA_CCR_PL_0;
	DMA2_Channel6->CCR |= DMA_CCR_DIR;
	DMA2_Channel6->CCR |= DMA_CCR_TCIE;

	NVIC_SetPriority(DMA2_Channel6_IRQn, 1);
	NVIC_EnableIRQ(DMA2_Channel6_IRQn);
}







