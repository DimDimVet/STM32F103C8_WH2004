#include "RCC_F103.h"

void RCC_Config(void)
{
    RCC_DeInit(); // Сбросить RCC
    RCC_HSEConfig(RCC_HSE_ON); // Включить HSE
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET)// Ожидать HSE
    {
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); // Настройка PLL 8 МГц * 9 = 72 МГц
        RCC_PLLCmd(ENABLE); // Включить PLL

        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) // Ожидать PLL
        {
            RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // Устанавливаем PLL как системный такт
        }
    }
}
