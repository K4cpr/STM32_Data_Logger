/*
 * lpuart.c
 *
 *  Created on: Feb 23, 2026
 *      Author: kapi-
 */

#include "main.h"
#include "lpuart.h"
#include "led.h"
#include <string.h>


LedPanel panelLED2;

volatile uint8_t BuffTX[128];
volatile int tx_index;
volatile uint32_t tx_busy = 0;

void LPUART1_config(void)
{
	//PC0 PLUART1 RX
	//PC1 LPUART1 TX

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
	//RX
	GPIOC->MODER &= ~(GPIO_MODER_MODE0_0);
	GPIOC->AFR[0] |= GPIO_AFRL_AFSEL0_3;

	//TX
	GPIOC->MODER &= ~(GPIO_MODER_MODE1_0);
	GPIOC->AFR[0] |= GPIO_AFRL_AFSEL1_3;

	LPUART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_UE);

	uint32_t BRR_VALUE = 256*(48000000/115200);
	LPUART1->BRR = BRR_VALUE;

	if(BRR_VALUE < 0x300 || BRR_VALUE > 0xFFFFF)
		{
			while(1){};
		}

	NVIC_SetPriority(LPUART1_IRQn, 1);
	NVIC_EnableIRQ(LPUART1_IRQn);

}

void GetStringLPUART1(char c[], uint32_t *char_ready)
{
	static int i;

		if(LPUART1->ISR & USART_ISR_RXNE)
			{
				char znak = LPUART1->RDR;
				if(znak == '\n')
					{
						 c[i] = '\0';
						 i = 0;
						 *char_ready = 1;
					}
				else
					{
						c[i++] = znak;
					}
			}
}

void LPUART1_IRQHandler(void)
{
	if(LPUART1->ISR & USART_ISR_TXE)
		{
			if(tx_busy == 1)
				{
					LPUART1->TDR = BuffTX[tx_index];
					tx_index ++;
					if(BuffTX[tx_index] == '\0')
						{
							LPUART1->CR1 &= ~(USART_CR1_TXEIE);
							tx_busy = 0;
							tx_index = 0;
						}
				}
		}
}

void SendString(char z[])
{
	int i = 0;
	for(int i = 0; i<127; i++)
		{
			BuffTX[i] = 0;
		}

	while(z[i] != '\0')
		{
			BuffTX[i] = z[i];
			i++;
		}

	BuffTX[i] = '\0';
	tx_busy = 1;
	tx_index = 0;

	LPUART1->CR1 |= USART_CR1_TXEIE;
}


