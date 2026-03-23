/*
 * sys_clocks.h
 *
 *  Created on: Dec 22, 2025
 *      Author: kapi-
 */

#ifndef SYS_CLOCKS_H_
#define SYS_CLOCKS_H_

void SystemClockSetup(void);
uint32_t GetSystemTick(void);
extern volatile uint32_t Tick;

void Delay(uint32_t Delay_ms);

#endif /* SYS_CLOCKS_H_ */
