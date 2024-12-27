#include "PWM.h"


void TIM1_PWM(int currentFreg, int autoReload)
{
    APB2_INIT_PERIPHERY(RCC_APB2ENR_TIM1EN);
    // Настройка таймера 1 для PWM

    TIM1->PSC = currentFreg - 1; // делим

    TIM1->ARR = autoReload - 1; // перегружаем
	
		TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1P;////настроим на выход канал 1, активный уровень низкий
		
		TIM1->BDTR |= TIM_BDTR_MOE; // Включить выходы
		
    TIM1->CCMR1 = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1; // Режим PWM

    TIM1->CR1 |= TIM_CR1_CEN; // Включить таймер
} 

void Set_TIM1_PWM(int level)
{
    if (level > 1000)
		{
			level = 1000; // Ограничение
		}
			
    TIM1->CCR1 = level; // Установка
}