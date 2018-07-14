/*Programa para el manejo del modulo LCD 1602L
 * Objetivo: Mostrar un mensaje y contador de segundos 00-59
 * Se requiere agregar los archivos "lcd.h" y "lcd.c"
 * Se trabaja con el PORTC utilizando 6 pines del RC0 al RC5
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#define LCD_PORT PORTC  //Define Datos LCD en PORTC
#define LCD_TRIS TRISC  //Define Control Datos LCD
#define LCD_RS PORTCbits.RC5    //Define pin RS LCD
#define LCD_EN PORTCbits.RC4    //Define pin EN LCD
#include "lcd.h"    //Agrega archivo de encabezado local LCD
char seg = 0;       //Variable de 8-bit para contar segundos
char msglcd[10];    //Lista o vector de 10 caracteres 8-bit
void main(void) //Funcion principal
{
    OSCCONbits.IRCF = 0b110; //Ajuste de Oscilador a 4Mhz
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    TRISC = 0b00000000; //Configura los pines del PORTC como salida
    LCDSetup(LINES2);   //Inicia el modulo LCD
    LCDPuts("HOLA");    //Envia la palabra Hola en primera linea
    while(1)
    {
        __delay_ms(1000);    //Retardo de 1 segundo
        seg++;  //Incrementa variable segundo
        if(seg >59) //Si seg es mayor a 59 
        {
            seg = 0;    //reinicia el valor en 0
        }
        LCDGoto(0x40);  //Posicionar el cursos LCD en la segunda linea 
        sprintf(msglcd, "T:%02u", seg);//Formatea el texto en la lista msglcd
        LCDPuts(msglcd); //Muestra la lista msglcd
    }
}
