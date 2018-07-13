/*********************************************************
 *  Libreria Basica para control de modulo LCD
 *  Autor: Pablo Zarate email:pablo@digital-bo.com
 *  Material de uso para aprendizaje en ELT436 U.E.B.
 *  (nota) El pin RW del LCD debe ser 0 logico
 *  Se debe definir los siguientes literales
 *  #define LCD_RS Pin de salida
 *  #define LCD_EN Pin de salida
 *  #define LCD_PORT Puerto Pines 0-3 
 *  #define LCD_TRIS Tris Pines 0-3
 * 
 *******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016 released beMicro.  All rights reserved.
beMicro autoriza el uso, modificacion,copia y distribucion de este software.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY 
INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS
OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS.
*******************************************************************************/
#define DelayForTCY() __delay_us(1) //req 1uS
#define DelayForTCY10() __delay_ms(1) //req 100us
#define DelayPORLCD() __delay_ms(15)//era 15ms
#define DelayLCD() __delay_ms(5)//era 5ms
/* MAY BE AND*/
#define DON         0x0F
#define DOFF        0x0B
#define CURSOR_ON   0x0F
#define CURSOR_OFF  0x0D
#define BLINK_ON    0x0F
#define BLINK_OFF   0x0E
/* MAY BE AND*/
#define CLEAR       0x01
#define HOME        0x02
#define LINES2		0x28	// Function set 2l 5x7
#define LINES1		0x20	// Function set 1l
#define LCDWriteCmd LCDSet
#define LCDWriteData LCDPutc
void LCDWriteData(char data);
void LCDWriteCmd(char cmd);
void LCDGoto(char DDaddr);
void LCDSetup(char mode);
void LCDPuts(char *str);
#include "lcd.c"
