/*
 * button.h
 *
 *  Created on: Feb 11, 2026
 *      Author: kapi-
 */

#ifndef BUTTON_H_
#define BUTTON_H_

extern volatile uint8_t Buff[4];

//configuration JOYSTICK
void button_init(void);

uint8_t buttonOK_pressed(void);
void buttonOK_clicked(void);
void buttonOK_clicked_Seg(void);


uint8_t buttonRT_pressed(void);
void buttonRT_clicked(void);
void buttonRT_clicked_Seg(void);

uint8_t buttonLT_pressed(void);
void buttonLT_clicked(void);
void buttonLT_clicked_Seg(void);

uint8_t buttonDN_pressed(void);
void buttonDN_clicked(void);
void buttonDN_clicked_Seg(void);

uint8_t buttonUP_pressed(void);
void buttonUP_clicked(void);
void buttonUP_clicked_Seg(void);


//UART



#endif /* BUTTON_H_ */
