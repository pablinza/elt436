/* Programa para utilizar el modulo TIMER2 para generar un tiempo 
 * de 20ms, o 50Hz. se utila un LED conectado a RC0 que destella a 
 * un intervalo de 0.5Seg.
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
char cnt = 0;	//Declara una variable contador iniciada en 0
bit ledst = off; //Declara un bit de estado para el LED 
void main()
{
   OSCSetup();	//Ajusta el oscilador interno a _XTAL_FREQ
   TRISCbits.TRISC0 = 0;//Configura el pin RC como salida
   TMR2Setup(T2PRE16, T2POS5);//Ajusta prescala 1:16 y posescala 1:5
   TMR2Setval(250); //Carga el valor del Periodo TMR2 para 20ms
   TMR2Start(); //Inicia el contador
   while(1)
   {
       if(PIR1bits.TMR2IF == 1) //Si ya pasaron 20ms
       {
           PIR1bits.TMR2IF = 0; //Limpia la bandera TMR2
           cnt ++; //Incremente el contador
       }
       if(cnt == 25) //Si el contador es 25 x 20ms = 500ms
       {
           cnt = 0; //Reinicia el contador
           PORTCbits.RC0 = ledst; //El LED se carga con el bit de estado
           ledst = !ledst; //el bit de estado cambia de logica
       }
   }
}
