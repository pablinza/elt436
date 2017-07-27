/* Programa para manejar los puertos entrada y salida digital
 * Manejo del display LCD, Mensajes basicos en las dos lineas
 * Cadenas personalizadas con sprintf y manejo de vector cadena
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF, MCLRE = OFF
#include <xc.h>
#include <ctype.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define LCD_TRIS TRISC  //Define el Registro de configuracion LCD
#define LCD_PORT PORTC  //Define el Puerto de datos LCD
#define LCD_RS PORTCbits.RC4 //Define el pin de control RS  
#define LCD_EN PORTCbits.RC5 //Define el pin de control EN
#include "lcd.h" //Agrega la libreria basica del LCD
char n = 0;
char msg[8];    //Configura un vector de caracteres con 8 posiciones
void main()
{
    OSCSetup(); //Ajusta el oscialdor a _XTAL_FREQ
    ANSEL = 0;  //Coloca en modo digital los pines ANS0-7
    ANSELH = 0; //Coloca en modo digital los pines ANS8-13
    TRISC = 0;  //Configura el PORTC como salida
    PORTC = 0;  //Establece el valor inicial del PORTC
    LCDSetup(LINES2);   //Inicia el LCD con dos lineas
    LCDPuts("CONTADOR"); //Escribe en el LCD la palabra 
    while(true)
    {
        LCDGoto(0x42);  //Situa el cursos en la posicion 65
        sprintf(msg, "%02u", n); //Personaliza la cadena en msg
        LCDPuts(msg);   //Escribe el contenido del vector msg
        delayms(980);   //Espera 980ms
        n = n+1;    //Incremente el contador de segundos
        if(n == 59) //Si el contador es mayor a 59
            n = 0;  //Reinicia el contador
    }
}