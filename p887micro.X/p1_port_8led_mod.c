/*Programa para el manejo de puertos Digitales del PIC16F887
 * Objetivo: Encendido secuencial de 8 leds conectados al PORTD
 * en funcion al estado de 2 pulsadores conectados a RB0 y RB1
 * Si RB0 es presionado el destello es hacia la derecha
 * Si RB1 es presionado el destello es hacia la izquierda
 * Mejora: Utiliza estructuras de control y variables
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
char leds;  //Variable de 8-bit para los leds
void rotA() //Procedimiento rotacion A
{
    leds = leds << 1; //desplaza una posicion bit a la izquierda
    if(leds == 0) //Si todos los bits son 0
    {
        leds = 0b00000001; //Coloca en alto solo el bit0
    }
    PORTD = ~leds; //Carga el PORTD con el valor complemento de la variable leds
    __delay_ms(100);
}
void rotB() //Procedimiento rotacion B
{
    leds = leds >> 1; //desplaza una posicion bit a la derecha
    if(leds == 0) //Si todos los bits con 0
    {
        leds = 0b10000000; //Coloca en alto el bit7
    }
    PORTD = ~leds; //Carga el PORTD con el valor complemento de la variable leds
    __delay_ms(100); 
}
void main(void) //Funcion principal
{
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    TRISD = 0b00000000; //Configura los pines del PORTD como salida
    TRISBbits.TRISB0 = 1; //Configura pulsador 1
    TRISBbits.TRISB1 = 1; //Configura pulsador 2
    while(1)
    {
        if(PORTBbits.RB0 == 0) //Si el pulsador 1 es presionado
        {
            rotA(); //Ejecuta procedimiento rotacion A
        } 
        if(PORTBbits.RB1 == 0)  //Si el pulsador 2 es presionado
        {
            rotB(); //Ejecuta procedimiento rotacion B
        }
    }
}
