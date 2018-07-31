/*Programa para el manejo del modulo ADC del PIC16F887
 * Objetivo: Medir el voltaje por un canal ADC y comparar
 * Conectar un potenciometro de 10K al pin RA0/AN0 para variar el 
 * voltaje que se medira con el ADC por el canal 0
 * Conectar un led a RB0 que indicara cuando el voltaje es menor 1V
 * Conectar un led a RB1 que indicara cuando el voltaje supere los 4V
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h" //Libreria de perifericos del PIC16F887
unsigned int pot;	//Variable para almacenar el valor de conversion pot
void main(void)
{
    ANSEL = 0;	//AN0-AN7 en modo digital
    ANSELH = 0;	//AN8-AN12 en modo digital
    ANSELbits.ANS0 = 1; //Activa entrada canal0
    TRISBbits.TRISB0 = 0; //Salida pin RB0
    TRISBbits.TRISB1 = 0; //Salida pin RB1
    PORTBbits.RB0 = 0;	//Apaga el LED al iniciar
    PORTBbits.RB1 = 0;	//Apaga el LED al iniciar
    ADCSetup();	//Configura e iniciar el modulo ADC
    while(1)
    {
        pot = ADCRead(0); //Lectura y conversion del canal 0
        if(pot < 200) //si port es menor a 1V
        {    
            PORTBbits.RB0 = 1; //Enciende Rb0
            PORTBbits.RB1 = 0; //Apaga Rb1
        }
        if(pot > 800) //Si pot mayor a 4V
        {
            PORTBbits.RB0 = 0; //Apaga RB0
            PORTBbits.RB1 = 1; //Enciende RB1
        }
        __delay_ms(10);	//Retardo 
    }
}
