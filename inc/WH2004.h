#ifndef WH2004_H_
#define WH2004_H_

#include "stm32f10x.h"
#include "delay.h"
#include "RCC_F103.h"

//4битная система, укажем какой пин подключаем (ODRх)
#define PIN_RS GPIO_ODR_ODR13
#define PIN_E GPIO_ODR_ODR14
#define PIN_D7 GPIO_ODR_ODR7
#define PIN_D6 GPIO_ODR_ODR6
#define PIN_D5 GPIO_ODR_ODR5
#define PIN_D4 GPIO_ODR_ODR15

//Инструкции WH2004
//delay=0 RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=0|DB3=0|DB2=0|DB1=0|DB0=0

#define CLEAR_DISPLAY 0x1//delay=1.52ms RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=0|DB3=0|DB2=0|DB1=0|DB0=1
#define RETURN_HOME 0x2//delay=1.52ms RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=0|DB3=0|DB2=0|DB1=1|DB0=0
#define ENTRY_MODE_SET 0x6 //delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=0|DB3=0|DB2=1|DB1=1|DB0=0
#define DISPLAY_ON 0xC //delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=0|DB3=1|DB2=1|DB1=0|DB0=0
#define DISPLAY_OFF 0x8//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=0|DB3=1|DB2=0|DB1=0|DB0=0
#define CURSOR_SHIFT_LEFT 0x10//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=1|DB3=0|DB2=0|DB1=0|DB0=0
#define CURSOR_SHIFT_RIGHT 0x14//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=1|DB3=0|DB2=1|DB1=0|DB0=0
#define DISPLAY_SHIFT_LEFT 0x18//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=1|DB3=1|DB2=0|DB1=0|DB0=0
#define DISPLAY_SHIFT_RIGHT 0x1C//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=0|DB4=1|DB3=1|DB2=1|DB1=0|DB0=0
#define DATA_BUS_4BIT_PAGE0 0x28//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0|DB3=1|DB2=0|DB1=0|DB0=0
#define DATA_BUS_4BIT_PAGE1 0x2A//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=0|DB3=1|DB2=0|DB1=1|DB0=0
#define DATA_BUS_8BIT_PAGE0 0x38//delay=37us RS=0|RW=0|DB7=0|DB6=0|DB5=1|DB4=1|DB3=1|DB2=0|DB1=0|DB0=0
#define SET_CGRAM_ADDRESS 0x40 //delay=37us RS=0|RW=0|DB7=0|DB6=1|DB5=0|DB4=0|DB3=0|DB2=0|DB1=0|DB0=0
#define SET_DDRAM_ADDRESS 0x80 //delay=37us RS=0|RW=0|DB7=1|DB6=0|DB5=0|DB4=0|DB3=0|DB2=0|DB1=0|DB0=0


#define   LCD_PORT               	GPIOB
#define		LCD_ODR 				LCD_PORT->ODR


void LCD_PIN_RS(void);
void LCD_PIN_E(void);
void LCD_PIN_D7(void);
void LCD_PIN_D6(void);
void LCD_PIN_D5(void);
void LCD_PIN_D4(void);

void LCD_INIT_MODE_4BIT(void); // инициализация WH2004 режим 4бит
void LCD_INIT(void); // основная инициализация

void SET_BYTE(char byte, int isData);
void PRINT_LCD( char *str, int row , int position ); // вывод строки

#endif

