/*Programa para el manejo de puertos Digitales del PIC16F887
 * Objetivo: Encendido secuencial de 8 leds conectados al PORTD
 * en funcion al estado de 2 pulsadores conectados a RB0 y RB1
 * Si RB0 es presionado el destello es hacia la derecha
 * Si RB1 es presionado el destello es hacia la izquierda
 */
 
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
void rotA() //Procedimiento rotacion A
{
    PORTD = ~0b00000001;
    __delay_ms(100);
    PORTD = ~0b00000010;
    __delay_ms(100);
    PORTD = ~0b00000100;
    __delay_ms(100);
    PORTD = ~0b00001000;
    __delay_ms(100);
    PORTD = ~0b00010000;
    __delay_ms(100);
    PORTD = ~0b00100000;
    __delay_ms(100);
    PORTD = ~0b01000000;
    __delay_ms(100);
    PORTD = ~0b10000000;
    __delay_ms(100);
}
void rotB() //Procedimiento rotacion B
{
    PORTD = ~0b10000000;
    __delay_ms(100);
    PORTD = ~0b01000000;
    __delay_ms(100);
    PORTD = ~0b00100000;
    __delay_ms(100);
    PORTD = ~0b00010000;
    __delay_ms(100);
    PORTD = ~0b00001000;
    __delay_ms(100);
    PORTD = ~0b00000100;
    __delay_ms(100);
    PORTD = ~0b00000010;
    __delay_ms(100);
    PORTD = ~0b00000001;
    __delay_ms(100);    
}

void main(void) //Funcion principal
{
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    TRISD = 0b00000000;
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
