/*Programa para el manejo del Teclado Matricial
 * Objetivo: Ingresar una clave digital y verificar si es 5050
 * Se requiere agregar los archivos "keypad.h" y "keypad.c"
 * Se requiere agregar los archivos "lcd.h" y "lcd.c"
 * El PORTC utilizando 6 pines del RC0 al RC5 para el LCD
 * El PORTB utilizando los 8 pines RB0 al RB7 para el Keypad
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _XTAL_FREQ 4000000
#define LCD_PORT PORTC  //Define Datos LCD en PORTC
#define LCD_TRIS TRISC  //Define Control Datos LCD
#define LCD_RS PORTCbits.RC5    //Define pin RS LCD
#define LCD_EN PORTCbits.RC4    //Define pin EN LCD
#include "lcd.h"    //Agrega archivo de encabezado local LCD

#define KB_PORT PORTB   //Define el Puerto de datos para el PAD
#define KB_TRIS TRISB   //Define el Registro de configuracion PAD
#include "keypad.h"     //Agrega la libreria basica del PAD

char val, key, num = 0, res;
char clave[8];
void main(void) //Funcion principal
{
    OSCCONbits.IRCF = 0b110; //Ajuste de Oscilador a 4Mhz
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    TRISC = 0b00000000; //Configura los pines del PORTC como salida
    LCDSetup(LINES2);   //Inicia el modulo LCD
    LCDPuts("CLAVE:");    //Envia la palabra Hola en primera linea
    LCDGoto(0x40);  //Posicionar el cursos LCD en la segunda linea 
    KBSetup();  //Inicializa el Keypad
    OPTION_REGbits.nRBPU = 0; //Habilita las pull-up del PORTB
    while(1)
    {
       val = KBScan(); //Hace una captura de PAD
       if(val != 0)    //Si el velor no es nulo
       {
            key = KBGetchar(val); //Recupera la tecla presionada
            if(key == '#')        //Si la tecla presionada es '#'
            {
                clave[num] = 0; //Fin de lista para la clave
                res = strcmp(clave, "5050"); //Si la clave es 5050
                if(res == 0)    
                {
                    LCDGoto(0x40);  //Posiciona el cursor en linea 2
                    LCDPuts("Correcto  "); 
                }
                else
                {
                    LCDGoto(0x40); //Posiciona el cursor en linea 2
                    LCDPuts("Incorrecto");      
                }
                __delay_ms(3000); //Retardo de 3 Segundos
                LCDSet(CLEAR);      //Limpia la pantalla
                LCDPuts("CLAVE:");  
                LCDGoto(0x40);
                num = 0;    //Inicia el contador de digitos
            }
            else
            {    
                LCDPutc(key);   //Escribe el valor de la tecla en el LCD
                clave[num] = key; //Almacena el valor en la lista
                num++;  //Incrementa el contador
            }
            __delay_ms(50);
        }
        __delay_ms(20);
    }
}
