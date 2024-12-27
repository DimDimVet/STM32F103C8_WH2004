#include "GPIO_F103.h"

void GPIO_INIT()
{
		//Запустим тактипрования PortC
	  APB2_INIT_PERIPHERY(RCC_APB2ENR_IOPCEN);
	  GPIO_LED_Config();
	//Запустим тактипрования PortB
	  APB2_INIT_PERIPHERY(RCC_APB2ENR_IOPAEN);
	  PWM_TIM1_Pin_Config();
}

void GPIO_LED_Config()
{
    GPIOC->CRH &=~(GPIO_CRH_CNF13|GPIO_CRH_MODE13);//0x0000
    GPIOC->CRH|=(~GPIO_CRH_CNF13)|GPIO_CRH_MODE13_1;//0x0010
		GPIOC->BSRR = GPIO_BSRR_BS13; // Установить
    GPIOC->BSRR = GPIO_BSRR_BR13; // Сбросить
}

void LED_Work()
{
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}

void PWM_TIM1_Pin_Config()//PA8
{
	  GPIOA->CRH &=~(GPIO_CRH_CNF8|GPIO_CRH_MODE8);//0x0000
    GPIOA->CRH|= GPIO_CRH_CNF8_1|GPIO_CRH_MODE8_1;//0x1010
		GPIOA->BSRR = GPIO_BSRR_BS8; // Установить
    GPIOA->BSRR = GPIO_BSRR_BR8; // Сбросить
}
