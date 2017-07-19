/* En este ejemplo se conocera la composicion del programa
 * declaracion de los fusibles y definiciones
 * se creara la libreria rutinas como rutinas.h
 * se agregara codigo de configuracion para el oscilador
 * Se aprendera a utilizar variables bit para pin.
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF, MCLRE = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define LEDpin PORTCbits.RC0 //Definicion para el pin RC0
bit ledbit;
void main()
{
    OSCSetup(); //Ajusta el oscilador interno
    TRISCbits.TRISC0 = 0; //Configura el pin RC0 como salida
    PORTCbits.RC0 = 0; //Coloca en 0 logico el pin RC0
    while(1)
    {
        delayms(100); //retardo
        LEDpin = 1; //Activa el LED
        delayms(100); //retardo
        LEDpin = 0; //Apaga el LED
    }
}
