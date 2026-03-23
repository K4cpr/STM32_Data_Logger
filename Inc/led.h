/*
 * led.h
 *
 *  Created on: Jan 28, 2026
 *      Author: kapi-
 */

#ifndef LED_H_
#define LED_H_
typedef struct
{
	GPIO_TypeDef *Port[3];
    uint32_t Pin[8];

} LedPanel;



//configuration led
void LedConf(void);
void Led_ON(LedPanel *panel, uint8_t idx, uint8_t idx2);
void Led_OFF(LedPanel *panel, uint8_t idx, uint8_t idx2);
void Led_TOGGLE(LedPanel *panel, uint8_t idx, uint8_t idx2);
void LPUART1_Menu(void);

//map pin led
void LedN_ON(LedPanel *p, uint8_t n);
void LedN_OFF(LedPanel *p, uint8_t n);
void LedN_TOGGLE(LedPanel *p, uint8_t n);

//panel led UART
void toggle(void);
void led_on(void);
void led_off(void);
void led_config(char c[]);
void LedUpdate(void);
void LedStart(uint8_t number_led);
uint8_t IsNumberLed(char c[]);


#endif /* LED_H_ */
