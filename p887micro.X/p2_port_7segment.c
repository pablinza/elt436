/*Programa para el manejo de los display de 7-Segmentos
 * Objetivo: Mostrar contador de segundos 00-59
 * Se requiere implementar un circuito con transistores para el
 * multiplexado en tiempo de cada modulo.
 * Se trabaja con el PORTD y PORTC conforme a esquema de circuito
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
char dmap[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
char seg = 0, lsb, msb, cnt = 0;
void main()
{
    ANSEL = 0;  //Coloca AN0-AN7 en modo digital
    ANSELH = 0; //Coloca AN8-AN13 en modo digital
    TRISCbits.TRISC0 = 0; //Configura el pin RC0 como salida display 1(MSB)
    TRISCbits.TRISC1 = 0; //Configura el pin RC1 como salida display 2(LSB)
    TRISD = 0;  //Configura todos los pines del PORTD como salida
    PORTD = 0;  //Coloca los pines del PORTD en 0 logico
    PORTC = 0;  //Coloca los pines del PORTC en 0 logico
    lsb = 0;    //Establece valor inicial 0 para el display 1
    msb = 0;    //Establece valor inicial 0 para el display 2
    while(1)
    {
        PORTD = dmap[lsb]; //Carga el PORTD con el valor menos significativo
        PORTCbits.RC1 = 1; //Activa el display 2
        __delay_ms(5);     //Espera 5ms
        PORTCbits.RC1 = 0; //Apaga el display 2
        PORTD = dmap[msb]; //Carga el PORTD con el valor mas significativo
        PORTCbits.RC0 = 1; //Activa el display 1
        __delay_ms(5);     //Espera 5ms
        PORTCbits.RC0 = 0; //Apaga el display 1
        cnt++;  //incrementa el contador 5ms + 5ms = 10ms por ciclo while
        if(cnt == 100)  //Pasa en 100 * 10ms = 1000ms
        {
            seg++;  //incrementa el contador de segundos
            if(seg > 59)  //si contador es mayor a 59 seg.
            {    
                seg = 0;  //reinicia el contador de segundos
            }
            msb = seg / 10; //carga en la variable los decimales del contador 
            lsb = seg % 10; //carga en la variable el residuo del contador 
            cnt = 0; //reinicia el contador de 10ms.
        }
    }
}