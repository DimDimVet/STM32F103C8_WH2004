#include "stm32f10x.h"
#include "WH2004.h"
#include "RCC_F103.h"
#include "GPIO_F103.h"
#include "PWM.h"
#include <stdio.h>

int main(void)
{
//
		RCC_Config();
	
    delay_ms(25);//ждем
		GPIO_INIT();
		TIM1_PWM(80);
		
    LCD_INIT();// инициализация портов и LCD
//		
		PRINT_LCD("Stroka1!+=", 1, 1);
    PRINT_LCD("stroka2!+=", 2, 1);
    PRINT_LCD("stroka3!+=", 3, 1);
    PRINT_LCD("stroka4!+=", 4, 1);
		
		int count=0;
		
    int number;
    char str [10];

		Set_TIM1_PWM(950);
		
    while (1)
    {

				count++;
				if(count > 50)
				{
						count=0;
						LED_Work();// Включить светодиод
				}

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

    }
}
