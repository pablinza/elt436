/* Programa para prueba del Microcontrolador PIC16F687
 * Objetivo: Destellar un led conectado al pin RA4
 */
#pragma config FOSC = INTRCIO, WDTE = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
void main(void)
{
    ANSEL = 0;	//AN0-AN7 en modo digital
    ANSELH = 0;	//AN8-AN12 en modo digital
    TRISAbits.TRISA4 = 0;	//RA4 como salida
    while(1)
    {
        PORTAbits.RA4 = 1;	//Activa RA4
        __delay_ms(500);
        PORTAbits.RA4 = 0;	//Desactiva RA4
        __delay_ms(500);
    }
}
