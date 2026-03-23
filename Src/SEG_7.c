/*
 * 7SEG.c
 *
 *  Created on: Feb 9, 2026
 *      Author: kapi-
 */

#include "main.h"
#include "SEG_7.h"
#include "lpuart.h"
#include <string.h>
#include "sys_clocks.h"

/*
PG0 - A
PG1 - B
PG2 - C
PG3 - D
PG4 - E
PG5 - F
PG6 - G

segments number
PB2 - 1
PB3 - 2
PB4 - 3
PB5 - 4
*/

volatile uint8_t Buff[4];
volatile uint16_t value = 0;
volatile uint32_t last_tick = 0;
volatile uint8_t stoper_run;


void Seg_7_Conf(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOGEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
	PWR->CR2 |= PWR_CR2_IOSV;

	GPIOB->MODER &= ~(GPIO_MODER_MODE2);
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	GPIOB->MODER &= ~(GPIO_MODER_MODE3);
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	GPIOB->MODER &= ~(GPIO_MODER_MODE4);
	GPIOB->MODER |= GPIO_MODER_MODE4_0;
	GPIOB->MODER &= ~(GPIO_MODER_MODE5);
	GPIOB->MODER |= GPIO_MODER_MODE5_0;

	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD4);
	GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD5);

	GPIOG->MODER &= ~(GPIO_MODER_MODE0);
	GPIOG->MODER |= GPIO_MODER_MODE0_0;
	GPIOG->MODER &= ~(GPIO_MODER_MODE1);
	GPIOG->MODER |= GPIO_MODER_MODE1_0;
	GPIOG->MODER &= ~(GPIO_MODER_MODE2);
	GPIOG->MODER |= GPIO_MODER_MODE2_0;
	GPIOG->MODER &= ~(GPIO_MODER_MODE3);
	GPIOG->MODER |= GPIO_MODER_MODE3_0;
	GPIOG->MODER &= ~(GPIO_MODER_MODE4);
	GPIOG->MODER |= GPIO_MODER_MODE4_0;
	GPIOG->MODER &= ~(GPIO_MODER_MODE5);
	GPIOG->MODER |= GPIO_MODER_MODE5_0;
	GPIOG->MODER &= ~(GPIO_MODER_MODE6);
	GPIOG->MODER |= GPIO_MODER_MODE6_0;
	GPIOG->MODER &= ~(GPIO_MODER_MODE9);
	GPIOG->MODER |= GPIO_MODER_MODE9_0;

}

void Seg_ON(char o)
{

	switch(o)
		{
			case 'A': GPIOG->BSRR |= GPIO_BSRR_BS0; break;
			case 'B': GPIOG->BSRR |= GPIO_BSRR_BS1; break;
			case 'C': GPIOG->BSRR |= GPIO_BSRR_BS2; break;
			case 'D': GPIOG->BSRR |= GPIO_BSRR_BS3; break;
			case 'E': GPIOG->BSRR |= GPIO_BSRR_BS4; break;
			case 'F': GPIOG->BSRR |= GPIO_BSRR_BS5; break;
			case 'G': GPIOG->BSRR |= GPIO_BSRR_BS6; break;
			case 'P': GPIOG->BSRR |= GPIO_BSRR_BS9; break;
		}

}

void Seg_On_place(int p)
{
	switch(p)
		{
			case 1: GPIOB->BSRR |= GPIO_BSRR_BS2; break;
			case 2: GPIOB->BSRR |= GPIO_BSRR_BS3; break;
			case 3: GPIOB->BSRR |= GPIO_BSRR_BS4; break;
			case 4: GPIOB->BSRR |= GPIO_BSRR_BS5; break;
		}
}

void Seg_OFF_place(int p)
{
	switch(p)
		{
			case 1: GPIOB->BSRR |= GPIO_BSRR_BR2; break;
			case 2: GPIOB->BSRR |= GPIO_BSRR_BR3; break;
			case 3: GPIOB->BSRR |= GPIO_BSRR_BR4; break;
			case 4: GPIOB->BSRR |= GPIO_BSRR_BR5; break;
		}
}

void Seg_OFF(char of)
{

	switch(of)
		{
			case 'A': GPIOG->BSRR |= GPIO_BSRR_BR0; break;
			case 'B': GPIOG->BSRR |= GPIO_BSRR_BR1; break;
			case 'C': GPIOG->BSRR |= GPIO_BSRR_BR2; break;
			case 'D': GPIOG->BSRR |= GPIO_BSRR_BR3; break;
			case 'E': GPIOG->BSRR |= GPIO_BSRR_BR4; break;
			case 'F': GPIOG->BSRR |= GPIO_BSRR_BR5; break;
			case 'G': GPIOG->BSRR |= GPIO_BSRR_BR6; break;
			case 'P': GPIOG->BSRR |= GPIO_BSRR_BR9; break;
		}
}

void Seg_number_On(int n, int p)
{
	Seg_OFF('A');
	Seg_OFF('B');
	Seg_OFF('C');
	Seg_OFF('D');
	Seg_OFF('E');
	Seg_OFF('F');
	Seg_OFF('G');
	Seg_OFF('P');

	switch(n)
		{
			case 0: Seg_ON('A'), Seg_ON('B'), Seg_ON('C'), Seg_ON('D'), Seg_ON('E'), Seg_ON('F'), Seg_On_place(p); break;
			case 1: Seg_ON('B'), Seg_ON('C'), Seg_On_place(p); break;
			case 2: Seg_ON('A'), Seg_ON('B'), Seg_ON('G'), Seg_ON('E'), Seg_ON('D'), Seg_On_place(p); break;
			case 3: Seg_ON('A'), Seg_ON('B'), Seg_ON('G'), Seg_ON('C'), Seg_ON('D'), Seg_On_place(p); break;
			case 4: Seg_ON('B'), Seg_ON('F'), Seg_ON('G'), Seg_ON('C'), Seg_On_place(p); break;
			case 5: Seg_ON('A'), Seg_ON('F'), Seg_ON('G'), Seg_ON('C'), Seg_ON('D'), Seg_On_place(p); break;
			case 6: Seg_ON('A'), Seg_ON('C'), Seg_ON('E'), Seg_ON('F'), Seg_ON('D'), Seg_ON('G'), Seg_On_place(p); break;
			case 7: Seg_ON('A'), Seg_ON('B'), Seg_ON('C'), Seg_On_place(p); break;
			case 8: Seg_ON('A'), Seg_ON('B'), Seg_ON('C'), Seg_ON('D'), Seg_ON('E'), Seg_ON('F'), Seg_ON('G'), Seg_On_place(p); break;
			case 9: Seg_ON('A'), Seg_ON('B'), Seg_ON('C'), Seg_ON('F'), Seg_ON('G'), Seg_On_place(p); break;
		}

}


void Seg_number_OFF(int n, int p)
{
	switch(n)
		{
			case 0: Seg_OFF('A'), Seg_OFF('B'), Seg_OFF('C'), Seg_OFF('D'), Seg_OFF('E'), Seg_OFF('F'), Seg_OFF_place(p); break;
			case 1: Seg_OFF('B'), Seg_OFF('C'), Seg_OFF_place(p); break;
			case 2: Seg_OFF('A'), Seg_OFF('B'), Seg_OFF('G'), Seg_OFF('E'), Seg_OFF('D'), Seg_OFF_place(p); break;
			case 3: Seg_OFF('A'), Seg_OFF('B'), Seg_OFF('G'), Seg_OFF('C'), Seg_OFF('D'), Seg_OFF_place(p); break;
			case 4: Seg_OFF('B'), Seg_OFF('F'), Seg_OFF('G'), Seg_OFF('C'), Seg_OFF_place(p); break;
			case 5: Seg_OFF('A'), Seg_OFF('F'), Seg_OFF('G'), Seg_OFF('C'), Seg_OFF('D'), Seg_OFF_place(p); break;
			case 6: Seg_OFF('A'), Seg_OFF('C'), Seg_OFF('E'), Seg_OFF('F'), Seg_OFF('D'), Seg_OFF('G'), Seg_OFF_place(p); break;
			case 7: Seg_OFF('A'), Seg_OFF('B'), Seg_OFF('C'), Seg_OFF_place(p); break;
			case 8: Seg_OFF('A'), Seg_OFF('B'), Seg_OFF('C'), Seg_OFF('D'), Seg_OFF('E'), Seg_OFF('F'), Seg_OFF('G'), Seg_OFF_place(p); break;
			case 9: Seg_OFF('A'), Seg_OFF('B'), Seg_OFF('C'), Seg_OFF('F'), Seg_OFF('G'), Seg_OFF_place(p); break;
		}

}



void Seg_4numbers_On(char c[])
{
	Buff[0] = SEG_BLANK;
	Buff[1] = SEG_BLANK;
	Buff[2] = SEG_BLANK;
	Buff[3] = SEG_BLANK;
	int len = strlen(c);
	uint8_t number;
	if(len <0 || len > 4)
		{
			return;
		}
		for(int i = 0; i < len; i++)
			{
				if(c[i] < '0' || c[i] > '9')
					{
						return;
					}
				number = c[i] - '0';
				Buff[i] = number;
			}

}

void Seg_RefreshStep(void)
{
	static uint8_t pole_aktualne = 1;
	uint8_t index = pole_aktualne - 1;
	uint8_t number = Buff[index];

	Seg_OFF_place(1);
	Seg_OFF_place(2);
	Seg_OFF_place(3);
	Seg_OFF_place(4);



	if(number < 10)
		{
			Seg_number_On(number, pole_aktualne);
		}

	if(pole_aktualne == 4)
		{
			pole_aktualne = 1;
		}
	else
		{
			pole_aktualne ++;
		}

}

void stoperStart(void)
{
	stoper_run = 1;
	last_tick = Tick;
}

void stoperStop(void)
{
	stoper_run = 0;
}

void stoperReset(void)
{
	value = 0;
	stoper_run = 0;
	Buff[0] = 0;
	Buff[1] = 0;
	Buff[2] = 0;
	Buff[3] = 0;
	last_tick = Tick;

}

void stoperUpdate(void)
{
	if(stoper_run == 1)
		{
			if((Tick - last_tick) >= 1000)
				{
					value++;
					last_tick = Tick;

					uint32_t wynik1 = value % 10;
					uint32_t wynik2 = (value / 10) % 10;
					uint32_t wynik3 = (value / 100) % 10;
					uint32_t wynik4 = value / 1000;

					Buff[0] = wynik4;
					Buff[1] = wynik3;
					Buff[2] = wynik2;
					Buff[3] = wynik1;

					if(value > 9999)
						{
							value = 0;
						}
				}
		}

}

uint8_t IsNumber(char z[])
{
	int len = strlen(z);
	if(len <0 || len > 4)
		{
			return 0;
		}
	for(int i = 0; i < len; i++)
		{
			if(z[i] < '0' || z[i] > '9')
				{
					return 0;
				}
		}
	return 1;
}



