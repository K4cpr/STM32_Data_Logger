# STM32 ADC DMA Data Logger

## Description
Simple data logger on STM32 using direct register programming (no HAL).

The project reads analog data, processes it, and sends results to a PC using UART DMA.  
ADC continuously samples the signal and transfers data to a memory buffer using DMA in circular mode.  
The buffer is periodically processed to compute the average value.  
A timer (TIM6) controls when data is sent.  
At each interval, the average value is converted to text and sent to a PC using UART DMA.

## Features
- ADC sampling  
- DMA (ADC - buffer, circular mode)  
- Averaging of samples  
- Timer (TIM6) for periodic transmission  
- UART transmission using DMA  

## Peripherals
- ADC1  
- DMA2 (Channel 3: ADC, Channel 6: UART TX)  
- LPUART1  
- TIM6  

## Tech
- STM32  
- C  
- Register-level programming (no HAL)  