/*
 * adc.h
 *
 *  Created on: Apr 19, 2026
 *      Author: kapi-
 */

#ifndef ADC_H_
#define ADC_H_

extern volatile uint16_t BuffAdc[];

void Adc_Gpio_Init(void);
void Adc_Config(void);
void Adc_Init(void);
uint16_t Adc_ReadTest(void);
uint32_t Adc_Volt_Read(void);
void AdcDmaStart(void);

uint8_t AdcResult(void);
uint16_t AdcResultAvg(void);


#endif /* ADC_H_ */
