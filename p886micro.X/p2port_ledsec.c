/* Programa para manejar los puertos entrada y salida digital
 secuenciador de 8 led con dezplazamiento izquierda o derecha
 presionando pulsador 1 o 2 
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF, MCLRE = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define SW1pin PORTBbits.RB0
#define SW2pin PORTBbits.RB1
char valorleds = 0b00010000; //Declara variable con valor inicial
void main()
{
    OSCSetup(); //Ajusta el oscilador interno
    ANSEL = 0;  //Configura los pines ANS0-7 en modo digital
    ANSELH = 0; //Configura los pines ANS8-13 en modo digital 
    TRISC = 0;  //Configura todos los pines del PORTC como salida
    TRISBbits.TRISB0 = 1;//Configura el pin RB0 como entrada
    TRISBbits.TRISB1 = 1;//Configura el pin RB1 como entrada
    EnablePU(); //Activa las resistencias pullup del PORTB
    PORTC = valorleds; //Coloca los pines del PORTC con un valor inicial
    while(true)
    {
        if(SW1pin == 0) //Si pulsador RB0 es presionado
        {
            valorleds = valorleds >> 1; //rotacion de un bit a la derecha
            if(valorleds == 0) //si la variable es 0
                valorleds = 0b10000000; //reinicia la variable
            PORTC = valorleds; //Coloca el PORTC con el valor
        }
        if(SW2pin == 0) //Si pulsador RB1 es presionado
        {
            valorleds = valorleds << 1; //rotacion de un bit a la izquierda
            if(valorleds == 0) //si la variable es 0
                valorleds = 0b00000001; //reinicia la variable
            PORTC = valorleds; //Coloca el PORTC con el valor
        }
        delayms(200); //Retardo entre desplazamiento        
    }
}