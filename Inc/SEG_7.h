/*
 * SEG_7.h
 *
 *  Created on: Feb 9, 2026
 *      Author: kapi-
 */

#ifndef SEG_7_H_
#define SEG_7_H_

#define SEG_BLANK 10
extern volatile uint8_t Buff[4];


//configuration 7Seg
void Seg_7_Conf(void);
void Seg_ON(char o);
void Seg_On_place(int p);
void Seg_OFF(char of);
void Seg_OFF_place(int p);
void Seg_number_On(int n, int p);
void Seg_number_OFF(int n, int p);
uint8_t IsNumber(char z[]);

//UART
void Seg_4numbers_On(char c[]);
void Seg_RefreshStep(void);

//STOPER
void stoperStart(void);
void stoperStop(void);
void stoperReset(void);
void stoperUpdate(void);

#endif /* SEG_7_H_ */
