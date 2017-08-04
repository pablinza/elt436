/* Practica XC8 para el manejo del modulo TIMER0
 * Conectar un led al pin RC0 y un pulsador a la entrada del contador TMR0
 * pin RA4/T0CK. el programa debe detectar 10 pulsos externos y activar el
 * led por 2 segundos, luego apagar y reiniciar nuevamente el ciclo
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
void main()
{
   OSCSetup();  //Ajusta oscilador interno a _XTAL_FREQ
   TRISCbits.TRISC0 = 0;    //Configura pin RC0 como salida
   PORTCbits.RC0 = 0;  //Apaga el led
   TMR0Setup(COUNTER, T0PRE1);//Ajusta el modo contador con prescala 1:1
   TMR0Setval(246);//Ajusta el valor para 10 pulsos. ver formula.
   while(1)
   {
       if(INTCONbits.TMR0IF == 1)//Verifica la bandera del TIMER0
       {
           PORTCbits.RC0 = on; //Activa el led
           delayms(2000);   //espera 2 segundos
           PORTCbits.RC0 = off;//Apaga el led
           TMR0Setval(246);//recarga el contador para 10 pulsos
       }
   }
}
