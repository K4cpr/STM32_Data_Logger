/*
 * lpuart.h
 *
 *  Created on: Feb 23, 2026
 *      Author: kapi-
 */

#ifndef LPUART_H_
#define LPUART_H_

void LPUART1_config(void);
void SendString(char z[]);

void LPUART1_IRQHandler(void);
void DMA2_CH6_IRQHandler(void);

void SendNumber(uint16_t num);

void SendStringDma(char z[]);
void SendNumberDma(uint16_t num);

#endif /* LPUART_H_ */
