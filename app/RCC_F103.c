#include "RCC_F103.h"

void RCC_Config(void)
{
    RCC_Reset();// Сбросить RCC

    RCC_HSE_Start(); // Включить HSE

    while (!READY_HSE())// Ожидать HSE
    {
        RCC_PLL_Config(); // Настройка PLL 8 МГц * 9 = 72 МГц
        RCC->CR |= RCC_CR_PLLON; // Включение PLL

        while (!READY_PLL()) // Ожидать PLL
        {
            RCC->CFGR |= RCC_CFGR_SW_PLL; // Выбор PLL в качестве системного такта
        }
    }
}

void RCC_PLL_Config()
{
    RCC->CFGR |= RCC_CFGR_PLLSRC_HSE; // Использовать HSE в качестве источника PLL
    RCC->CFGR |= RCC_CFGR_PLLMULL9; // Умножитель PLL = 9 (8 МГц * 9 = 72 МГц)
}

int READY_PLL()
{
    return(RCC->CR & RCC_CR_PLLRDY);//опросим RCC_CR_HSERDY
}

int READY_HSE()
{
    return(RCC->CR & RCC_CR_HSERDY);//опросим RCC_CR_HSERDY
}

void RCC_Reset()
{
    /* Set HSION bit */
    RCC->CR |= RCC_CR_HSION;

    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= ~(RCC_CFGR_SW|RCC_CFGR_HPRE|RCC_CFGR_PPRE1|RCC_CFGR_PPRE2|RCC_CFGR_ADCPRE);

    /* Reset HSEON, CSSON and PLLON bits, Reset HSEBYP bit */
    RCC->CR &= ~(RCC_CR_HSEON|RCC_CR_CSSON|RCC_CR_PLLON|RCC_CR_HSEBYP);

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC|RCC_CFGR_PLLXTPRE|RCC_CFGR_PLLMULL|RCC_CFGR_USBPRE);

    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;
}

void RCC_HSE_Start()
{
    RCC->CR |= RCC_CR_HSEON; // Включение HSE
}

//RCC
void APB2_INIT_PERIPHERY(int RCC_PERIPHERY)
{
    RCC->APB2ENR |= RCC_PERIPHERY;
}

void APB1_INIT_PERIPHERY(int RCC_PERIPHERY)
{
    RCC->APB1ENR |=RCC_PERIPHERY;
}

