/*Programa para utilizar el modulo TMR2
 * Objetivo: Destellar un led conectado al pin RC0 cada segundo donde solo 
 * este encendido el 20% del periodo, utilizar el servicio a la interrupcion
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
char f1cnt = 0, f1ok = 0; //Contador y Bandera para control del led
char pinRC0 = 0; //Variable para guardar estado del pin RC0
void interrupt isr()
{
    if(PIR1bits.TMR2IF == 1) //Verifica si hay interrupcion TMR2
    {
        PIR1bits.TMR2IF = 0;    //Limpia la bandera
        f1cnt ++;   //Incrementa el contrador de 10ms
        if(f1cnt == 10) PORTCbits.RC0 = 0;  //Apaga el led al 20%
        if(f1cnt > 49)  //si paso un segungo (50 * 20ms)
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
    TMR2Setup(T2PRE16, T2POS8); //Temporizador con pre-escala 1:16 y Post 1:8
    TMR2Setperiod(156); //PR2 = (4000000 * 0.020)/(4 * 16 * 8) Ajuste para 20ms
    INTCONbits.PEIE = 1;//Activa la interrupcion de perifericos adicionales
    PIE1bits.TMR2IE = 1;//Activa la interrupcion del TMR2
    INTCONbits.GIE = 1; //Habilita las interrupciones
    TMR2Start();    //Arranca el timer
    while(1)
    {
        if(f1ok == 1)
        {
            f1ok = 0;
            PORTCbits.RC0 = 1; //Activa el led
        }
    }
}
