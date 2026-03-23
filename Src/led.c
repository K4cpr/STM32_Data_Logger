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
#include "SEG_7.h"
#include "sys_clocks.h"
#include "button.h"

LedPanel panelLED3;

uint8_t page = 0;
uint8_t seg_mode = 0;
uint8_t joy_mode = 0;

volatile uint32_t last_tick1 = 0;
volatile uint8_t led_run;
volatile uint8_t led_state = 0;
volatile uint8_t licznik = 0;
volatile uint8_t led_num = 0;
volatile uint8_t Command_Ok;

#define PAGE_MENU 0
#define PAGE_LED  1
#define PAGE_SEG  2
#define PAGE_JOY  3

#define SEG_MASK 0
#define SEG_STOPER 1
#define SEG_SEG 2

#define JOY_LED 0
#define JOY_SEG 1
#define JOY_JOY 2

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



void LPUART1_Menu(void)
{
	static char z[32];
	static uint32_t charready = 0;


	GetStringLPUART1(z, &charready);

			if(charready == 1)
			{
				Command_Ok = 0;
				if(strcmp(z, "menu") == 0)
					{
					Command_Ok = 1;
					SendString("\r\n\r\n\r\n\r\n\r\n===== MENU =====\r\nCommands:\r\nLedControl\r\n7SegControl\r\nJoyControl\r\n\r\n\r\n\r\n\r\n");
					page = PAGE_MENU;
					led_off();
					Buff[0] = SEG_BLANK;
					Buff[1] = SEG_BLANK;
					Buff[2] = SEG_BLANK;
					Buff[3] = SEG_BLANK;
					LedStart(0);
					}

				else if(strcmp(z, "LedControl") == 0)
					{
					Command_Ok = 1;
					SendString("\r\n\r\n\r\n\r\n\r\n\r\n===== LedControl =====\r\nCommands:\r\nmenu\r\n7SegControl\r\nJoyControl\r\ntoggle\r\nled_on\r\nled_off\r\n0...7\r\n\r\n");
					page = PAGE_LED;
					led_off();
					Buff[0] = SEG_BLANK;
					Buff[1] = SEG_BLANK;
					Buff[2] = SEG_BLANK;
					Buff[3] = SEG_BLANK;
					LedStart(1);
					}
				else if(strcmp(z, "7SegControl") == 0)
					{
					Command_Ok = 1;
					SendString("\r\n\r\n\r\n===== 7SegControl =====\r\nCommands:\r\nmenu\r\nLedControl\r\nJoyControl\r\nmask\r\nstoper\r\n\r\n\r\n\r\n\r\n");
					page = PAGE_SEG;
					seg_mode = SEG_SEG;
					led_off();
					Buff[0] = SEG_BLANK;
					Buff[1] = SEG_BLANK;
					Buff[2] = SEG_BLANK;
					Buff[3] = SEG_BLANK;
					LedStart(2);
					}
				else if(strcmp(z, "JoyControl") == 0)
					{
					Command_Ok = 1;
					SendString("\r\n\r\n\r\n\r\n\r\n===== JoyControl =====\r\nCommands:\r\nmenu\r\nLedControl\r\n7SegControl\r\nLED\r\n7SEG\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
					page = PAGE_JOY;
					joy_mode = JOY_JOY;
					led_off();
					Buff[0] = SEG_BLANK;
					Buff[1] = SEG_BLANK;
					Buff[2] = SEG_BLANK;
					Buff[3] = SEG_BLANK;
					LedStart(3);
					}
				else
				{
					if(page == PAGE_MENU)
					{
						//
					}
					else if(page == PAGE_LED)
					{

						if(strcmp(z, "toggle") == 0)
						{
							Command_Ok = 1;
							toggle();
						}
						else if(strcmp(z, "led_on") == 0)
						{
							Command_Ok = 1;
							led_on();
						}
						else if(strcmp(z, "led_off")==0)
						{
							Command_Ok = 1;
							led_off();
						}
						else
						{
							if(IsNumberLed(z))
							{
								Command_Ok = 1;
								led_config(z);
							}
							else
							{
								SendString("\r\n===== Invalid Commands =====\r\n");
							}
						}
					}
					else if(page == PAGE_SEG)
						{
						if(strcmp(z, "mask") == 0)
						 	{
								Command_Ok = 1;
								SendString("\r\n\r\n\r\n\r\n===== mask =====\r\nCommands:\r\nset mask [num,num,num,num]\r\nstoper\r\nmenu\r\nLedControl\r\nJoyControl\r\n\r\n\r\n");
						     	seg_mode = SEG_MASK;
								Buff[0] = SEG_BLANK;
								Buff[1] = SEG_BLANK;
								Buff[2] = SEG_BLANK;
								Buff[3] = SEG_BLANK;
						     	LedStart(4);
						    }
						else if(strcmp(z, "stoper") == 0)
						    {
								Command_Ok = 1;
								SendString("\r\n\r\n\r\n\r\n===== stoper =====\r\nCommands:\r\nstart_stoper\r\nstop_stoper\r\nreset_stoper\r\nmask\r\nmenu\r\nLedControl\r\nJoyControl\r\n\r\n\r\n");
						        seg_mode = SEG_STOPER;
								Buff[0] = SEG_BLANK;
								Buff[1] = SEG_BLANK;
								Buff[2] = SEG_BLANK;
								Buff[3] = SEG_BLANK;
						        LedStart(5);
						    }

						else if(seg_mode == SEG_MASK)
							{
								if(IsNumber(z))
								{
									Command_Ok = 1;
									Seg_4numbers_On(z);
								}
								else
								{
									SendString("\r\n===== Invalid Commands =====\r\n");
								}
							}
						else if(seg_mode == SEG_STOPER)
							{
							if(strcmp(z, "start_stoper") == 0)
								{
									Command_Ok = 1;
									stoperStart();
								}
							else if(strcmp(z, "reset_stoper") == 0)
								{
									Command_Ok = 1;
									stoperReset();
								}
							else if(strcmp(z, "stop_stoper") == 0)
								{
									Command_Ok = 1;
									stoperStop();
								}
							}
						}
					else if(page == PAGE_JOY)
						{
						if(strcmp(z, "LED") == 0)
							{
								Command_Ok = 1;
								SendString("\r\n\r\n\r\n===== MECHANICAL LED CONTROL =====\r\nCommands:\r\nmenu\r\nLedControl\r\nJoyControl\r\n\r\n\r\n\r\n\r\n");
								joy_mode = JOY_LED;
								led_off();
								Buff[0] = SEG_BLANK;
								Buff[1] = SEG_BLANK;
								Buff[2] = SEG_BLANK;
								Buff[3] = SEG_BLANK;
								LedStart(6);
							}
						else if(strcmp(z, "7SEG") == 0)
							{
								Command_Ok = 1;
								SendString("\r\n\r\n\r\n===== MECHANICAL 7SEG CONTROL =====\r\nCommands:\r\nmenu\r\nLedControl\r\nJoyControl\r\n\r\n\r\n\r\n\r\n");
								joy_mode = JOY_SEG;
								led_off();
								Buff[0] = SEG_BLANK;
								Buff[1] = SEG_BLANK;
								Buff[2] = SEG_BLANK;
								Buff[3] = SEG_BLANK;
								LedStart(7);
							}
						else if(joy_mode == JOY_LED)
							{

							}
						else if(joy_mode == JOY_SEG)
							{
								//
							}

						}
				}
				if(Command_Ok == 0)
					{
						SendString("\r\n===== Invalid Commands =====\r\n");
					}
				charready = 0;
			}
			if(page == PAGE_SEG && seg_mode == SEG_STOPER)
			    {
			        stoperUpdate();
			    }
			if(page == PAGE_MENU || page == PAGE_LED || page == PAGE_SEG || page == PAGE_JOY || seg_mode == SEG_STOPER || seg_mode == SEG_MASK)
				{
					LedUpdate();
				}
			if(page == PAGE_JOY && joy_mode == JOY_LED)
				{
					buttonOK_clicked();
					buttonLT_clicked();
					buttonRT_clicked();
					buttonUP_clicked();
					buttonDN_clicked();
				}
			if(page == PAGE_JOY && joy_mode == JOY_SEG)
				{
					buttonUP_clicked_Seg();
					buttonRT_clicked_Seg();
					buttonLT_clicked_Seg();
					buttonDN_clicked_Seg();
					buttonOK_clicked_Seg();
				}


}

void toggle(void)
{
	for(int i = 0; i<9; i++)
		{
			LedN_TOGGLE(&panelLED3, i);
		}
}

void led_on(void)
{
	for(int i = 0; i<9; i++)
		{
			LedN_ON(&panelLED3, i);
		}
}

void led_off(void)
{
	for(int i = 0; i<9; i++)
		{
			LedN_OFF(&panelLED3, i);
		}
}

void led_config(char c[])
{
	int len = strlen(c);
	uint8_t number;
	for(int i = 0; i < len; i++)
		{
			if(c[i] < '0' || c[i] > '7')
			{
				if(c[i] == '\r' || c[i] == '\n')
					{
						break;
					}
				else
					{
						continue;
					}
			}

			number = c[i] - '0';
			LedN_TOGGLE(&panelLED3, number);
		}
}

void LedUpdate(void)
{

	if(led_run == 1)
	{
		if(licznik < 6)
		{

		if((Tick - last_tick1) >= 500)
			{
				last_tick1 = Tick;
				if(led_state == 1)
					{
						LedN_OFF(&panelLED3, led_num);
						led_state = 0;
					}
				else if(led_state == 0)
					{
						LedN_ON(&panelLED3, led_num);
						led_state = 1;
					}
				licznik ++;
				if(licznik == 6)
					{
						led_run = 0;
						licznik = 0;
						LedN_OFF(&panelLED3, led_num);
					}
			}
		}
	}
}

void LedStart(uint8_t number_led)
{
	led_num = number_led;
	led_run = 1;
	licznik = 0;
	last_tick1 = Tick;
	led_state = 0;
}

uint8_t IsNumberLed(char c[])
{
	int len = strlen(c);
	for(int i = 0; i < len; i++)
		{
			if(c[i] < '0' || c[i] > '7')
				{
					return 0;
				}
		}
	return 1;
}





