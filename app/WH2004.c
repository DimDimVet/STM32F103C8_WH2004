#include "WH2004.h"

void SET_BYTE(char byte, int isData)
{
    if(isData == 1)
    {
        LCD_ODR |= PIN_RS;   // рабочий режим RS=1
    }
    else
    {
        LCD_ODR &= ~(PIN_RS);   // режим инициализации RS=0
    }
		
		//Начало Фаза1
    //сбросим все пины дисплея
    LCD_ODR &= ~(PIN_E | PIN_D7 | PIN_D6 | PIN_D5 | PIN_D4);

    // ставим D7|D6|D5|D4|x|x|x|x в порт
    if(byte & 0x80) LCD_ODR |= PIN_D7;
    if(byte & 0x40) LCD_ODR |= PIN_D6;
    if(byte & 0x20) LCD_ODR |= PIN_D5;
    if(byte & 0x10) LCD_ODR |= PIN_D4;

    // вкл-выкл пин E
    LCD_ODR |= PIN_E;
    LCD_ODR &= ~PIN_E;
		//Конец Фаза1
		//Начало Фаза2
		//сбросим все пины дисплея
    LCD_ODR &= ~(PIN_E | PIN_D7 | PIN_D6 | PIN_D5 | PIN_D4);

    // ставим x|x|x|x|D3|D2|D1|D0 в порт
    if(byte & 0x8) LCD_ODR |= PIN_D7;
    if(byte & 0x4) LCD_ODR |= PIN_D6;
    if(byte & 0x2) LCD_ODR |= PIN_D5;
    if(byte & 0x1) LCD_ODR |= PIN_D4;

		// вкл-выкл пин E
    LCD_ODR |= PIN_E;
    LCD_ODR &= ~PIN_E;
		//Конец Фаза2
		
    delay_us(40);
}

void LCD_INIT()
{
		//Запустим тактипрования PortB
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    LCD_PIN_RS();
    LCD_PIN_E();
    LCD_PIN_D7();
    LCD_PIN_D6();
    LCD_PIN_D5();
    LCD_PIN_D4();

    LCD_INIT_MODE_4BIT();
}

// назначим порты STM32F103 к пинам WH2004
void LCD_PIN_RS()// RS = PB13
{
    LCD_PORT->CRH &= ~GPIO_CRH_CNF13;
    LCD_PORT->CRH |= GPIO_CRH_MODE13;
}

void LCD_PIN_E()// E = PB14
{
    LCD_PORT->CRH &= ~GPIO_CRH_CNF14;
    LCD_PORT->CRH |= GPIO_CRH_MODE14;
}

void LCD_PIN_D7()// D7 = PB7
{
    LCD_PORT->CRL &= ~GPIO_CRL_CNF7;
    LCD_PORT->CRL |= GPIO_CRL_MODE7;
}

void LCD_PIN_D6()// D6 = PB6
{
    LCD_PORT->CRL &= ~GPIO_CRL_CNF6;
    LCD_PORT->CRL |= GPIO_CRL_MODE6;
}

void LCD_PIN_D5()// D5 = PB5
{
    LCD_PORT->CRL &= ~GPIO_CRL_CNF5;
    LCD_PORT->CRL |= GPIO_CRL_MODE5;
}

void LCD_PIN_D4()// D15 = PB15
{
    LCD_PORT->CRH &= ~GPIO_CRH_CNF15;
    LCD_PORT->CRH |= GPIO_CRH_MODE15;
}

//Общая инициализация WH2004
void LCD_INIT_MODE_4BIT(void)
{
    delay_ms(40); // Подождите более 40 мс после того, как VDD поднимется до 4,5 В

    SET_BYTE(0x30, 0); // Установим RS=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1|DB3=0|DB2=0|DB1=0|DB0=0
    delay_us(39);

    SET_BYTE(0x32, 0); // // Установим RS=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1|DB3=0|DB2=0|DB1=1|DB0=0
    delay_us(39);

    SET_BYTE(DATA_BUS_4BIT_PAGE0, 0); // включаем режим 4 бит
    delay_us(37);
		
    SET_BYTE(DISPLAY_OFF, 0); // выключаем 
    delay_us(37);
		
    SET_BYTE(CLEAR_DISPLAY, 0); // очищаем 
    delay_ms(2);
		
    SET_BYTE(ENTRY_MODE_SET, 0); //ставим режим смещение курсора экран
    delay_us(40);
		
    SET_BYTE(DISPLAY_ON, 0);// включаем и убираем курсор
    delay_us(40);
}

void PRINT_LCD(char *str, int row, int position )
{

    char start_address;

    switch (row)
    {

    case 1:
        start_address = 0x0; // 1 строка
        break;

    case 2:
        start_address = 0x40; // 2 строка
        break;

    case 3:
        start_address = 0x14; // 3 строка
        break;

    case 4:
        start_address = 0x54; // 4 строка
        break;

    }

    start_address += position; // к началу строки прибавляем позицию в строке

    SET_BYTE((start_address |= SET_DDRAM_ADDRESS), 0); // ставим курсор на начало нужной строки  в DDRAM

    delay_ms(4);
		
		//по символьно выведем тектс
    while(*str != '\0')
    {
        SET_BYTE(*str, 1);
        str++;
    }
}

