/*
 * adc.h
 *
 *  Created on: Apr 19, 2026
 *      Author: kapi-
 */

#ifndef ADC_H_
#define ADC_H_

void Adc_Gpio_Init(void);
void Adc_Config(void);
void Adc_Init(void);
uint32_t Adc_Read(void);
uint32_t Adc_Volt_Read(void);

#endif /* ADC_H_ */
