/* Practica XC8 para el manejo del modulo TIMER0
 * Conectar un led al pin RC0 para cambiar su estado cada 0,5seg
 * utilizando el modulo TIMER0. 
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
char cnt = 0;   //declara variable contador
bit ledst = off;//declara variable de estado para el led
void main()
{
   OSCSetup();  //Ajusta oscilador interno a _XTAL_FREQ
   TRISCbits.TRISC0 = 0;    //Configura pin RC0 como salida
   PORTCbits.RC0 = 0;  //Apaga el led
   TMR0Setup(TIMER, T0PRE64);//Ajusta el modo timer con prescala 1:64
   TMR0Setval(99);//Ajusta el valor de 99 para 10ms. ver formula.
   while(1)
   {
       if(INTCONbits.TMR0IF == 1) //Verifica la bandera del TIMER0
       {
           TMR0Setval(99);  //reinicia el timer para 10ms
           cnt ++;  //incrementa la variable
       }
       if(cnt == 50)    //si la variable es 50 x 10ms = 500ms
       {
           cnt = 0; //reinicia la variable
           PORTCbits.RC0 = ledst;//asigna un valor al pin RC0
           ledst = !ledst; //cambia el estado logico del valor led.
       }
   }
}