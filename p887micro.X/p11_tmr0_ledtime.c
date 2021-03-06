/*Programa para utilizar el modulo TMR0
 * Objetivo: Destellar un led conectado al pin RC0 cada segundo
 * utilizando el servicio a la interrupcion
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
char f1cnt = 0, f1ok = 0; //Contador y Bandera para control del led
char pinRC0 = 0; //Variable para guardar estado del pin RC0
void interrupt isr()
{
    if(INTCONbits.T0IF == 1) //Verifica si hay interrupcion TMR0
    {
        INTCONbits.T0IF = 0;    //Limpia la bandera
        TMR0Setval(100); //TMR0 = 256 - [(0.010/64) * (4000000/4)] Ajuste para 10ms
        f1cnt ++;   //Incrementa el contrador de 10ms
        if(f1cnt > 99)  //si paso un segungo (99 * 10ms)
        {
            f1cnt = 0;  //Reinicia contador
            f1ok = 1;   //Activa bandera de control led
        }
    }
}

void main(void) //Funcion principal
{
    OSCSetup(); //Ajuste el oscilador a frec _XTAL_FREQ
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    TRISCbits.TRISC0 = 0; //Configura en pin RC0 como salida
    TMR0Setup(TIMER, T0PRE64); //Temporizador con pre-escala 1:64
    TMR0Setval(100); //TMR0 = 256 - [(0.010/64) * (4000000/4)] Ajuste para 10ms
    INTCONbits.T0IE = 1;    //Activa la interrupcion del TMR0
    INTCONbits.GIE = 1; //Habilita las interrupciones
    while(1)
    {
        if(f1ok == 1)
        {
            f1ok = 0;
            PORTCbits.RC0 = pinRC0;
            pinRC0 = !pinRC0;
            
        }
    }
}
