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
#include "adc.h"

LedPanel panelLED2;
volatile uint32_t BuffTx[128];
volatile int tx_busy;
volatile uint32_t tx_index = 0;



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

void LPUART1_IRQHandler(void)
{
	if(LPUART1->ISR & USART_ISR_TXE)
	{
		if(tx_busy == 1)
		{
				LPUART1->TDR = BuffTx[tx_index];
				tx_index ++;
				if(BuffTx[tx_index] == '\0')
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
	while(tx_busy == 1)
	{
	}
	int copy_index = 0;

	while(z[copy_index] != '\0')
	{
		BuffTx[copy_index] = z[copy_index];
		copy_index ++;
	}
	BuffTx[copy_index] = '\0';
	tx_busy = 1;
	tx_index = 0;

	LPUART1->CR1 |= USART_CR1_TXEIE;

}


void SendNumber(uint16_t num)
{
	char BuffNumber[5];

	uint16_t wynik1 = num % 10;
	uint16_t wynik2 = (num / 10) % 10;
	uint16_t wynik3 = (num / 100) % 10;
	uint16_t wynik4 = num / 1000;

	char text1 = wynik4 + '0';
	char text2 = wynik3 + '0';
	char text3 = wynik2 + '0';
	char text4 = wynik1 + '0';
	char text5 = '\0';

	BuffNumber[0] = text1;
	BuffNumber[1] = text2;
	BuffNumber[2] = text3;
	BuffNumber[3] = text4;
	BuffNumber[4] = text5;

	uint8_t start = 0;
	while((BuffNumber[start] == '0') && start < 3)
	{
		start++;

	}


	if(num > 9999)
		{
			SendString("OVF");
		}
	else
		{
			SendString(start + BuffNumber);
		}

}














