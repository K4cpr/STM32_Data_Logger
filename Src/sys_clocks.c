/*
 * sys_clocks.c
 *
 *  Created on: Dec 22, 2025
 *      Author: kapi-
 */

#include "main.h"
#include "sys_clocks.h"
#include "SEG_7.h"
volatile uint32_t Tick;

void SystemClockHSI16(void)
{
	// HSI ON
	RCC->CR |= RCC_CR_HSION;

	// wait for HSI
	while ((RCC->CR & RCC_CR_HSIRDY) == 0) { }

	// CHANGE SWITCH
	 RCC->CFGR &= ~RCC_CFGR_SW;
	 RCC->CFGR |= RCC_CFGR_SW_HSI;

	// WAIT FOR SWITCH
	 while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) { }



}



void SystemClockPLL48(void)
{

// SYSTEM CLOCK MUX TO PLL
// PLL SOURCE MUX / DZIELNIKI HSI ZOSTAJE
	// HSI ON
	RCC->CR |= RCC_CR_HSION;

	// wait for HSI
	while ((RCC->CR & RCC_CR_HSIRDY) == 0) { }

	//HSI AND PLL SOURCE

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC); // CLEAR TWO BIT
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_HSI); // SET 1 BIT TO (10)

	FLASH->ACR &= ~(FLASH_ACR_LATENCY);  // CELAR BITS
	FLASH->ACR |= FLASH_ACR_LATENCY_2WS; // SET 4 WS ON FLASH

	while (!(FLASH->ACR & FLASH_ACR_LATENCY_2WS));


	// DIVIDERS

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM); // CLEAR ALL 4 BITS ON PLLM

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN); // CLEAR ALL BITS ON PLLM
	RCC->PLLCFGR |= (12 << RCC_PLLCFGR_PLLN_Pos); // TO CLARIFY !!!

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR); // CLEAR ALL 2 BITS ON PLLR
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLR_0; // SET 01

	//PLL ENABLE
	// PLL ON
	RCC->CR |= RCC_CR_PLLON;

	// wait for HSI
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) { }

	//PLL OUTPUT ENABLE

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN; // SET 1

	// CHANGE SWITCH TO PLL

	 RCC->CFGR |= RCC_CFGR_SW_1;
	 RCC->CFGR |= RCC_CFGR_SW_0;

	// WAIT FOR SWITCH
	 while (!((RCC->CFGR & RCC_CFGR_SWS_1) && (RCC->CFGR & RCC_CFGR_SWS_0))) { }



}

void SystemClockPLL80(void)
{

// SYSTEM CLOCK MUX TO PLL
// PLL SOURCE MUX / DZIELNIKI HSI ZOSTAJE
	// HSI ON
	RCC->CR |= RCC_CR_HSION;

	// wait for HSI
	while ((RCC->CR & RCC_CR_HSIRDY) == 0) { }

	//HSI AND PLL SOURCE

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC); // CLEAR TWO BIT
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_HSI); // SET 1 BIT TO (10)


	FLASH->ACR &= ~(FLASH_ACR_LATENCY);  // CELAR BITS
	FLASH->ACR |= FLASH_ACR_LATENCY_4WS; // SET 4 WS ON FLASH

	while (!(FLASH->ACR & FLASH_ACR_LATENCY_4WS));

	// DIVIDERS

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM); // CLEAR ALL 4 BITS ON PLLM

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN); // CLEAR ALL BITS ON PLLM
	RCC->PLLCFGR |= (10 << RCC_PLLCFGR_PLLN_Pos); // TO CLARIFY !!!

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR); // CLEAR ALL 2 BITS ON PLLR
	//RCC->PLLCFGR |= RCC_PLLCFGR_PLLR_0; // SET 01

	//PLL ENABLE
	// PLL ON
	RCC->CR |= RCC_CR_PLLON;

	// wait for HSI
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) { }

	//PLL OUTPUT ENABLE

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN; // SET 1

	// CHANGE SWITCH TO PLL

	 RCC->CFGR |= RCC_CFGR_SW_1;
	 RCC->CFGR |= RCC_CFGR_SW_0;

	// WAIT FOR SWITCH
	 while (!((RCC->CFGR & RCC_CFGR_SWS_1) && (RCC->CFGR & RCC_CFGR_SWS_0))) { }



}

void SystemClockSetup(void)
{
//	SystemClockHSI16();
	SystemClockPLL48();
//	SystemClockPLL80();
	SysTick_Config(48000000 / 1000);
}

void SysTick_Handler(void)
{
	Tick++;
	Seg_RefreshStep();
}


uint32_t GetSystemTick(void)
{
	return Tick;
}


// Delay WARNING Blocking
void Delay(uint32_t Delay_ms)
{
	uint32_t StartTime = Tick;
	while(Tick < (StartTime + Delay_ms))
	{
		//wait
	}
}








