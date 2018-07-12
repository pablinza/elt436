/* Programa para prueba del Microcontrolador PIC16F887
 * Objetivo: Destellar un led conectado al pin RE2
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
void main(void)
{
    ANSEL = 0;	//AN0-AN7 en modo digital
    ANSELH = 0;	//AN8-AN12 en modo digital
    TRISEbits.TRISE2 = 0;	//RE2 como salida
    while(1)
    {
        PORTEbits.RE2 = 1;	//Activa RE2
        __delay_ms(500);
        PORTEbits.RE2 = 0;	//Desactiva RE2
        __delay_ms(500);
    }
}
