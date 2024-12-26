#ifndef RCC_F103_H_
#define RCC_F103_H_

#include "stm32f10x.h"

void RCC_Config(void);
void RCC_Reset(void);
void RCC_HSE_Start(void);
int READY_HSE(void);
void RCC_PLL_Config(void);
int READY_PLL(void);

#endif
