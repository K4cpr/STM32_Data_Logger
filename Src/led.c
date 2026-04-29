/*
 * led.c
 *
 *  Created on: Jan 28, 2026
 *      Author: kapi-
 */

#include "main.h"
#include "led.h"
#include "lpuart.h"
#include <string.h>
#include "sys_clocks.h"



void LedConf(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;

	GPIOC->MODER &= ~(GPIO_MODER_MODE6);
	GPIOC->MODER |= GPIO_MODER_MODE6_0;

	GPIOC->MODER &= ~(GPIO_MODER_MODE7);
	GPIOC->MODER |= GPIO_MODER_MODE7_0;

	GPIOC->MODER &= ~(GPIO_MODER_MODE8);
	GPIOC->MODER |= GPIO_MODER_MODE8_0;

	GPIOC->MODER &= ~(GPIO_MODER_MODE9);
	GPIOC->MODER |= GPIO_MODER_MODE9_0;

	GPIOE->MODER &= ~(GPIO_MODER_MODE4);
	GPIOE->MODER |= GPIO_MODER_MODE4_0;

	GPIOD->MODER &= ~(GPIO_MODER_MODE3);
	GPIOD->MODER |= GPIO_MODER_MODE3_0;

	GPIOE->MODER &= ~(GPIO_MODER_MODE5);
	GPIOE->MODER |= GPIO_MODER_MODE5_0;

	GPIOE->MODER &= ~(GPIO_MODER_MODE6);
	GPIOE->MODER |= GPIO_MODER_MODE6_0;

}


void Led_ON(LedPanel *panel, uint8_t idx, uint8_t idx2)
{

	panel->Pin[0] = GPIO_BSRR_BS6;
	panel->Pin[1] = GPIO_BSRR_BS7;
	panel->Pin[2] = GPIO_BSRR_BS8;
	panel->Pin[3] = GPIO_BSRR_BS9;
	panel->Pin[4] = GPIO_BSRR_BS4;
	panel->Pin[5] = GPIO_BSRR_BS3;
	panel->Pin[6] = GPIO_BSRR_BS5;
	panel->Pin[7] = GPIO_BSRR_BS6;

	panel->Port[0] = GPIOC;
	panel->Port[1] = GPIOE;
	panel->Port[2] = GPIOD;

	panel->Port[idx]->BSRR = panel->Pin[idx2];

}

void Led_OFF(LedPanel *panel, uint8_t idx, uint8_t idx2)
{

	panel->Pin[0] = GPIO_BSRR_BR6;
	panel->Pin[1] = GPIO_BSRR_BR7;
	panel->Pin[2] = GPIO_BSRR_BR8;
	panel->Pin[3] = GPIO_BSRR_BR9;
	panel->Pin[4] = GPIO_BSRR_BR4;
	panel->Pin[5] = GPIO_BSRR_BR3;
	panel->Pin[6] = GPIO_BSRR_BR5;
	panel->Pin[7] = GPIO_BSRR_BR6;

	panel->Port[0] = GPIOC;
	panel->Port[1] = GPIOE;
	panel->Port[2] = GPIOD;

	panel->Port[idx]->BSRR = panel->Pin[idx2];

}


void Led_TOGGLE(LedPanel *panel, uint8_t idx, uint8_t idx2)
{

	panel->Pin[0] = GPIO_ODR_OD6;
	panel->Pin[1] = GPIO_ODR_OD7;
	panel->Pin[2] = GPIO_ODR_OD8;
	panel->Pin[3] = GPIO_ODR_OD9;
	panel->Pin[4] = GPIO_ODR_OD4;
	panel->Pin[5] = GPIO_ODR_OD3;
	panel->Pin[6] = GPIO_ODR_OD5;
	panel->Pin[7] = GPIO_ODR_OD6;

	panel->Port[0] = GPIOC;
	panel->Port[1] = GPIOE;
	panel->Port[2] = GPIOD;

	panel->Port[idx]->ODR ^= panel->Pin[idx2];

}

//MAP PINS ON LED

void LedN_ON(LedPanel *p, uint8_t n)
{
    switch(n)
    {
        case 0: Led_ON(p, /*port*/0, /*pin*/0); break;
        case 1: Led_ON(p, 0, 1); break;
        case 2: Led_ON(p, 0, 2); break;
        case 3: Led_ON(p, 0, 3); break;
        case 4: Led_ON(p, 1, 4); break;
        case 5: Led_ON(p, 2, 5); break;
        case 6: Led_ON(p, 1, 6); break;
        case 7: Led_ON(p, 1, 7); break;
        default: break;
    }
}

void LedN_OFF(LedPanel *p, uint8_t n)
{
	 switch(n)
	 {
	    case 0: Led_OFF(p, /*port*/0, /*pin*/0); break;
	    case 1: Led_OFF(p, 0, 1); break;
	    case 2: Led_OFF(p, 0, 2); break;
	    case 3: Led_OFF(p, 0, 3); break;
	    case 4: Led_OFF(p, 1, 4); break;
	    case 5: Led_OFF(p, 2, 5); break;
	    case 6: Led_OFF(p, 1, 6); break;
	    case 7: Led_OFF(p, 1, 7); break;
	    default: break;
	 }
}

void LedN_TOGGLE(LedPanel *p, uint8_t n)
{
    switch(n)
    {
    	case 0: Led_TOGGLE(p, /*port*/0, /*pin*/0); break;
    	case 1: Led_TOGGLE(p, 0, 1); break;
    	case 2: Led_TOGGLE(p, 0, 2); break;
    	case 3: Led_TOGGLE(p, 0, 3); break;
    	case 4: Led_TOGGLE(p, 1, 4); break;
    	case 5: Led_TOGGLE(p, 2, 5); break;
    	case 6: Led_TOGGLE(p, 1, 6); break;
    	case 7: Led_TOGGLE(p, 1, 7); break;
    	default: break;
    }
}








