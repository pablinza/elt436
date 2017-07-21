/* Programa para manejar los puertos entrada y salida digital del PIC
 * Uso del 2 Display de 7 Segmentos conectados al PORTC del PIC utilizando
 * el multiplexado por tiempo, cada display es activado con un transistor
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF, MCLRE = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define DP1pin PORTAbits.RA0 //Define el pin de activacion para el Display 1
#define DP2pin PORTAbits.RA1 //Define el pin de activacion para el Display 2
char dmap[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
char n = 0, lsb, msb, cnt = 0;
void main()
{
    OSCSetup(); //Ajusta el oscilador interno a _XTAL_FREQ
    ANSEL = 0;  //Coloca AN0-AN7 en modo digital
    ANSELH = 0; //Coloca AN8-AN13 en modo digital
    TRISAbits.TRISA0 = 0; //Configura el pin RA0 como salida display 1.
    TRISAbits.TRISA1 = 0; //Configura el pin RA1 como salida display 2.
    TRISC = 0;  //Configura todos los pines del PORTC como salida
    PORTA = 0;  //Coloca los pines del PORTA en 0 logico
    PORTC = 0;  //Coloca los pines del PORTC en 0 logico
    lsb = 0;    //Establece valor inicial 0 para el display 1
    msb = 0;    //Establece valor inicial 0 para el display 2
    while(true)
    {
        PORTC = dmap[lsb]; //Carga el PORTC con el valor menos significativo
        DP1pin = on;    //Activa el display 1
        delayms(5);     //Espera 5ms
        DP1pin = off;   //Desactiva el display 1
        PORTC = dmap[msb]; //Carga el PORTC con el valor mas significativo
        DP2pin = on;    //Activa el display 2
        delayms(5);     //Espera 5ms
        DP2pin = off;   //Desactiva el display 2
        cnt = cnt + 1;  //incrementa el contador de 10ms (5ms + 5ms)
        if(cnt == 100)  //si el tiempo es (5ms+5ms) * 100 = 1000ms
        {
            n = n + 1;  //incrementa el contador de segundos
            if(n > 59)  //si contador es mayor a 59 seg.
                n = 0;  //reinicia el contador de segundos
            msb = n / 10; //carga en la variable los decimales del contador 
            lsb = n % 10; //carga en la variable el residuo del contador 
            cnt = 0; //reinicia el contador de 10ms.
        }
    }
}
/* PRACTICA QUIEN ARMA UN CRONOMETRO CON SS:mil START, STOP, RESET*/