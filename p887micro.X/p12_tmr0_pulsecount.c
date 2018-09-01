/*Programa para utilizar el modulo TMR0
 * Objetivo: Detectar 25 pulsos externos en el pin RA4/T0CK y activar
 * un led conectado al pin RC0, utilizar el servicio a la interrupcion
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
char f1ok = 0; //Bandera para control de led
void interrupt isr()
{
    if(INTCONbits.T0IF == 1) //Verifica si hay interrupcion TMR0
    {
        INTCONbits.T0IF = 0;    //Limpia la bandera
        TMR0Setval(231); //Re-ajuste para 25 pulsos
        f1ok = 1;   //Activa bandera de control led
    }
}

void main(void) //Funcion principal
{
    OSCSetup(); //Ajuste el oscilador a frec _XTAL_FREQ
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    TRISCbits.TRISC0 = 0; //Configura en pin RC0 como salida
    TMR0Setup(COUNTER, T0PRE1); //Contador con pre-escala 1:1
    TMR0Setval(231); //TMR0 = 256 - [(25/1)] Ajuste para 25 pulsos
    INTCONbits.T0IE = 1;    //Activa la interrupcion del TMR0
    INTCONbits.GIE = 1; //Habilita las interrupciones
    while(1)
    {
        if(f1ok == 1)
        {
            f1ok = 0;
            PORTCbits.RC0 = 1;  //Enciende el led
            __delay_ms(2000); //Espera de 2ms
            PORTCbits.RC0 = 0;  //Apaga el led 
        }
    }
}
