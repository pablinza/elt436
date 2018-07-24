/* Programa para manejo de la interrupcion externa INT
 * Objetivo: Elaborar un programa para control de un semaforo
 * para dos intersecciones, que se coloque en estado de emergencia
 * en caso de una falla en cualquier indicador de señal.
 * Las luces de la calle 1 son Rojo1=RC0 Amarillo1=RC1 Verde1=RC2
 * Las luces de la calle 2 son Rojo2=RD0 Amarillo2=RD1 Verde2=RD2
 * La entrada de señal para alerta o falla es el pin RB0 
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000

void interrupt isr()    //Rutina de servicio a la interrupcion
{
    if(INTCONbits.INTF == 1) //Verifica si la badera 
    {
        while(PORTBbits.RB0 == 1) //Miestras pin de falla este en 1 logico
        {
            PORTC = 0;  //Apaga las luces R1 A1 V1 calle 1
            PORTD = 0;  //Apaga las luces R2 A2 V2 calle 2
            __delay_ms(300); 
            PORTCbits.RC1 = 1; //Enciende la luz amarilla A1
            PORTDbits.RD1 = 1; //Enciende la luz amarilla A2
            __delay_ms(300);
        }
        INTCONbits.INTF = 0; //Limpia la bandera de interrucion externa
    }
}

void main(void) //Funcion principal
{
    OSCCONbits.IRCF = 0b110; //Ajuste de Oscilador a 4Mhz
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    TRISD = 0;  //Configura los pines del PORTD como salida
    TRISC = 0;  //Configura los pines del PORTC como salida
    PORTD = 0;  //Coloca en 0 logicos todos los pines del PORTD
    TRISC = 0;  //Coloca en 0 logico todos los pines del PORTC
    TRISBbits.TRISB0 = 1; //Configura como entrada el pin RB0 falla
    OPTION_REGbits.INTEDG = 1; //Dectecta flanco ascendente
    INTCONbits.INTE = 1;    //Habilita la interrupcion externa INT
    INTCONbits.GIE = 1; //Habilitador Global
    while(1)
    {
        PORTCbits.RC0 = 1;  //Enciende luz roja R1
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 0;
        PORTDbits.RD0 = 0;  
        PORTDbits.RD1 = 0;
        PORTDbits.RD2 = 1;  //Enciende luz verde V2
        __delay_ms(10000);
        PORTDbits.RD2 = 0;  //Apaga luz verde V2
        PORTDbits.RD1 = 1;  //Enciende luz amarilla A2
        __delay_ms(2000);
        PORTCbits.RC0 = 0;  //Apaga luz roja R1
        PORTCbits.RC2 = 1;  //Enciende luz verde V1
        PORTDbits.RD1 = 0;  //Apaga luz amarilla A2  
        PORTDbits.RD0 = 1;  //Enciende luz roja R2
        __delay_ms(10000);
        PORTCbits.RC2 = 0;  //Apaga luz verde V1
        PORTCbits.RC1 = 1;  //Enciende luz amarilla A1
        __delay_ms(2000);
    }
}
