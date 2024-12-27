#ifndef GPIO_F103_H_
#define GPIO_F103_H_

#include "stm32f10x.h"
#include "RCC_F103.h"

void GPIO_INIT(void);
void GPIO_LED_Config(void);
void LED_Work(void);
void PWM_TIM1_Pin_Config(void);

#endif