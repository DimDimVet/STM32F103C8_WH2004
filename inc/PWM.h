#ifndef PWM_H_
#define PWM_H_

#include "stm32f10x.h"
#include "RCC_F103.h"

void TIM1_PWM(int currentFreg);
void Set_TIM1_PWM(int level);

#endif