/*
 * button.c
 *
 *  Created on: Feb 11, 2026
 *      Author: kapi-
 */

#include "main.h"
#include "button.h"
#include "led.h"
#include "SEG_7.h"

volatile uint8_t button_stanLT = 0;
volatile uint8_t button_currentLT;
volatile uint8_t number_led = 0;
volatile uint8_t last_number_ledLT = 0;
volatile uint32_t last_button_tickLT = 0;

volatile uint8_t joy_led_enable = 0;

volatile uint8_t button_stanOK = 0;
volatile uint8_t button_currentOK;
volatile uint8_t last_number_ledOK = 0;
volatile uint32_t last_button_tickOK = 0;

volatile uint8_t button_stanRT = 0;
volatile uint8_t button_currentRT;
volatile uint8_t last_number_ledRT = 0;
volatile uint32_t last_button_tickRT = 0;

volatile uint8_t button_stanUP = 0;
volatile uint8_t button_currentUP;
volatile uint8_t last_number_ledUP = 0;
volatile uint32_t last_button_tickUP = 0;

volatile uint8_t button_stanDN = 0;
volatile uint8_t button_currentDN;
volatile uint8_t last_number_ledDN = 0;
volatile uint32_t last_button_tickDN = 0;

volatile uint8_t button_stanUP_Seg = 0;
volatile uint8_t button_currentUP_Seg;
volatile uint8_t last_number_ledUP_Seg = 0;
volatile uint32_t last_button_tickUP_Seg = 0;

volatile uint8_t button_stanRT_Seg = 0;
volatile uint8_t button_currentRT_Seg;
volatile uint8_t last_number_ledRT_Seg = 0;
volatile uint32_t last_button_tickRT_Seg = 0;

volatile uint8_t button_stanLT_Seg = 0;
volatile uint8_t button_currentLT_Seg;
volatile uint8_t last_number_ledLT_Seg = 0;
volatile uint32_t last_button_tickLT_Seg = 0;

volatile uint8_t button_stanDN_Seg = 0;
volatile uint8_t button_currentDN_Seg;
volatile uint8_t last_number_ledDN_Seg = 0;
volatile uint32_t last_button_tickDN_Seg = 0;

volatile uint8_t button_stanOK_Seg = 0;
volatile uint8_t button_currentOK_Seg;
volatile uint8_t last_number_ledOK_Seg = 0;
volatile uint32_t last_button_tickOK_Seg = 0;


volatile uint8_t seg_pos = 0;
volatile uint8_t seg_blink_enable = 0;

LedPanel panelLED4;

void button_init(void)
{
	//PE15 - center
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~(GPIO_MODER_MODE15);
	//PE0 - RIGHT
	GPIOE->MODER &= ~(GPIO_MODER_MODE0);
	//PE1 - LEFT
	GPIOE->MODER &= ~(GPIO_MODER_MODE1);
	//PE2 - DN
	GPIOE->MODER &= ~(GPIO_MODER_MODE2);
	//PE3 - UP
	GPIOE->MODER &= ~(GPIO_MODER_MODE3);
}

uint8_t buttonOK_pressed(void)
{
	if(GPIOE->IDR & GPIO_IDR_ID15)
		{
			return 0;
		}

	return 1;
}

void buttonOK_clicked(void)
{
	button_currentOK = buttonOK_pressed();

	if(button_currentOK == 1 && button_stanOK == 0 && (Tick - last_button_tickOK) > 30)
		{
			LedN_TOGGLE(&panelLED4, number_led);
			last_button_tickOK = Tick;
			joy_led_enable = !joy_led_enable;
		}

	button_stanOK = button_currentOK;
}

uint8_t buttonLT_pressed(void)
{
	if(GPIOE->IDR & GPIO_IDR_ID1)
		{
			return 1;
		}

	return 0;
}

void buttonLT_clicked(void)
{
	button_currentLT = buttonLT_pressed();

	if(joy_led_enable == 1)
		{
			if(button_currentLT == 1 && button_stanLT == 0 && (Tick - last_button_tickLT) > 30)
				{

					last_number_ledLT = number_led;

					if(number_led == 7)
						{
							number_led = 0;
						}
					else
						{
							number_led = number_led + 1;
						}

					LedN_OFF(&panelLED4, last_number_ledLT);
					LedN_ON(&panelLED4, number_led);
					last_button_tickLT = Tick;

				}

			button_stanLT = button_currentLT;
		}
}

uint8_t buttonRT_pressed(void)
{
	if(GPIOE->IDR & GPIO_IDR_ID0)
		{
			return 1;
		}
	return 0;
}

void buttonRT_clicked(void)
{

	button_currentRT = buttonRT_pressed();
	if(joy_led_enable == 1)
		{
			if(button_currentRT == 1 && button_stanRT == 0 && (Tick - last_button_tickRT) > 30)
				{
					last_number_ledRT = number_led;

					if(number_led == 0)
						{
							number_led = 7;
						}
					else
						{
							number_led = number_led - 1;
						}

					LedN_OFF(&panelLED4, last_number_ledRT);
					LedN_ON(&panelLED4, number_led);
					last_button_tickLT = Tick;

				}

			button_stanRT = button_currentRT;
		}

}

uint8_t buttonDN_pressed(void)
{
	if(GPIOE->IDR & GPIO_IDR_ID2)
		{
			return 1;
		}

	return 0;
}

void buttonDN_clicked(void)
{
	button_currentDN = buttonDN_pressed();

	if(button_currentDN == 1 && button_stanDN == 0 && (Tick - last_button_tickDN) > 30)
		{
			led_off();
			last_button_tickLT = Tick;
			joy_led_enable = 0;
		}

	button_stanDN = button_currentDN;
}

uint8_t buttonUP_pressed(void)
{
	if(GPIOE->IDR & GPIO_IDR_ID3)
		{
			return 1;
		}

	return 0;
}

void buttonUP_clicked(void)
{
	button_currentUP = buttonUP_pressed();

	if(button_currentUP == 1 && button_stanUP == 0 && (Tick - last_button_tickUP) > 30)
		{
			led_on();
			last_button_tickUP = Tick;
			joy_led_enable = 0;
		}

	button_stanUP = button_currentUP;

}


void buttonUP_clicked_Seg(void)
{
	button_currentUP_Seg = buttonUP_pressed();

	if(button_currentUP_Seg == 1 && button_stanUP_Seg == 0 && (Tick - last_button_tickUP_Seg) > 60)
		{
			Buff[seg_pos] = (Buff[seg_pos] + 1) % 10;
			last_button_tickUP_Seg = Tick;
		}

	button_stanUP_Seg = button_currentUP_Seg;
}

void buttonRT_clicked_Seg(void)
{
	button_currentRT_Seg = buttonRT_pressed();

	if(button_currentRT_Seg == 1 && button_stanRT_Seg == 0 && (Tick - last_button_tickRT_Seg) > 60)
		{
			seg_pos++;
			if(seg_pos > 3)
				{
					seg_pos = 0;
				}
			last_button_tickRT_Seg = Tick;
		}

	button_stanRT_Seg = button_currentRT_Seg;
}

void buttonLT_clicked_Seg(void)
{
	button_currentLT_Seg = buttonLT_pressed();

	if(button_currentLT_Seg == 1 && button_stanLT_Seg == 0 && (Tick - last_button_tickLT_Seg) > 60)
		{
			if(seg_pos == 0)
				{
					seg_pos = 3;
				}
			else
				{
					seg_pos--;
				}
			last_button_tickLT_Seg = Tick;
		}

	button_stanLT_Seg = button_currentLT_Seg;
}

void buttonDN_clicked_Seg(void)
{
	button_currentDN_Seg = buttonDN_pressed();

	if(button_currentDN_Seg == 1 && button_stanDN_Seg == 0 && (Tick - last_button_tickDN_Seg) > 60)
		{
			if(Buff[seg_pos] == 0)
				{
					Buff[seg_pos] = 9;
				}
			else
				{
					Buff[seg_pos]--;
				}
			last_button_tickDN_Seg = Tick;
		}

	button_stanDN_Seg = button_currentDN_Seg;

}

void buttonOK_clicked_Seg(void)
{
	button_currentOK_Seg = buttonOK_pressed();

	if(button_currentOK_Seg == 1 && button_stanOK_Seg == 0 && (Tick - last_button_tickOK_Seg) > 60)
		{
			Buff[0] = 0;
			Buff[1] = 0;
			Buff[2] = 0;
			Buff[3] = 0;
			last_button_tickOK_Seg = Tick;
		}

	button_stanOK_Seg = button_currentOK_Seg;
}



