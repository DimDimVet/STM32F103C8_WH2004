#include "stm32f10x.h"
#include "WH2004.h"
#include "RCC_F103.h"
#include <stdio.h>


void GPIO_ConfigLed(void);

int main(void)
{
		RCC_Config();
    delay_ms(25);//ждем
    LCD_INIT();// инициализация портов и LCD


//SET_BYTE(0xB8, 1);
//SET_BYTE(0xC0, 1);


		PRINT_LCD("Stroka1!+=", 1, 1);
    PRINT_LCD("stroka2!+=", 2, 1);
    PRINT_LCD("stroka3!+=", 3, 1);
    PRINT_LCD("stroka4!+=", 4, 1);
		
    int number;
    char str [10];

    GPIO_ConfigLed();
		
    while (1)
    {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);  // Включить светодиод
        number++;
        if(number>100)
        {
            number=0;
        }
				
        snprintf(str, sizeof str, "%d", number);
        PRINT_LCD(str, 1, 15);
        PRINT_LCD(str, 2, 14);
        PRINT_LCD(str, 3, 13);
				PRINT_LCD(str, 4, 12);
				
        delay_s(1);                     // Задержка
        GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Выключить светодиод
        delay_s(1);
    }
}

void GPIO_ConfigLed(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Включить тактирование порта C

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;        // Pin PC13
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // Режим выхода, Push-Pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // Скорость 50 МГц
    GPIO_Init(GPIOC, &GPIO_InitStructure);              // Инициализация
}

