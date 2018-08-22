/* Programa para prueba del Microcontrolador PIC12F675
 * Objetivo: Destellar un led conectado al pin GP0
 */
#pragma config FOSC = INTRCIO, WDTE = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
void main(void)
{
    ANSEL = 0;	//AN0-AN7 en modo digital
    TRISIObits.TRISIO0 = 0;	//GP0 como salida
    while(1)
    {
        GPIObits.GP0 = 1;
        __delay_ms(500);
        GPIObits.GP0 = 0;
        __delay_ms(500);
    }
}
