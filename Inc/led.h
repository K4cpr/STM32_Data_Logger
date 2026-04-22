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


//map pin led
void LedN_ON(LedPanel *p, uint8_t n);
void LedN_OFF(LedPanel *p, uint8_t n);
void LedN_TOGGLE(LedPanel *p, uint8_t n);



#endif /* LED_H_ */
