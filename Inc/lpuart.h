/*
 * lpuart.h
 *
 *  Created on: Feb 23, 2026
 *      Author: kapi-
 */

#ifndef LPUART_H_
#define LPUART_H_

void LPUART1_config(void);
//void LPUART1_Receiv_Led(void);
void GetStringLPUART1(char c[], uint32_t *char_ready);

void SendString(char z[]);
void LPUART1_IRQHandler(void);



#endif /* LPUART_H_ */
