/*Programa para manejar la interrupcion por cambio de estado RB
 * Objetivo: Conectar cuatro pulsadores en el PORTB y 2 leds a 
 * los pines RC0 y RC1, un led debe destellar cada segundo y el
 * otro led cambiara de estado cuando la entrada logica de cualquier
 * pulsador tambien cambie.
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
char datob; //Variable temporal para leer el valor del PORTB
char led2value = 0; //Variable para guardar el estado del segundo led D2
void interrupt isr()
{  
    if(INTCONbits.RBIF == 1) //Verifica si es la interrupcion por cambio
    {
        led2value = !led2value; //Cambia la logica (0->1) o (1->0)de la variable
        PORTCbits.RC1 = led2value;  //Actualiza el pin con el valor de la variable
        datob = PORTB;  //Iguala la condicion actual
        INTCONbits.RBIF = 0; //Limpia la bandera
    }
    
}
void main()
{
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0xFF;   //Todos los pines del PORTB en modo entrada 
    TRISC = 0;      //Todos los pines del PORTC en modo salida
    PORTC = 0;      //Coloca en 0 los pines del PORTC
    IOCBbits.IOCB0 = 1; //Habilita el pin RB0 para cambio de estado
    IOCBbits.IOCB1 = 1; //Habilita el pin RB1 para cambio de estado
    IOCBbits.IOCB2 = 1; //Habilita el pin RB2 para cambio de estado
    IOCBbits.IOCB3 = 1; //Habilita el pin RB3 para cambio de estado
    OPTION_REGbits.nRBPU = 0;   //Activa las pull-ups del PORTB
    INTCONbits.RBIE = 1; //Habilita interrup por cambio de estado en PORTB
    INTCONbits.GIE = 1; //Habilitador global
    while(1)
    {
        PORTCbits.RC0 = 1;  //Enciende el led D1
        __delay_ms(500);
        PORTCbits.RC0 = 0;  //Apaga el led D1
        __delay_ms(500);
    }
    
}
