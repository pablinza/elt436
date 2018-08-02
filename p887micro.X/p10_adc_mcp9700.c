/*  Programa para manejar un sensor de Temperatura MCP9700 
 * Objetivo: Realizar un programa que lea la temperatura de un
 * sensor MCP9700 conectado al pin AN0, y envie su valor por el
 * puerto seria.
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
unsigned int tem; //Variable para almacenar la temperatura
unsigned int temsum; //Variable para guardar suma y hacer promedio
char lista[16], c = 0;
void main(void)
{
    ANSEL = 0;	//AN0-AN7 en modo digital
    ANSELH = 0;	//AN8-AN12 en modo digital
    ANSELbits.ANS0 = 1; //Activa entrada canal0
    ADCSetup(); //Configura el modulo ADC
    UARTSetup(9600);    //Configura el modulo Serial
    while(1)
    {
        
        tem = ADCRead(0) - 100; //Lectura y conversion del canal 0
        temsum = temsum + tem;
        c++;    //Incrementa el contador
        if(c == 50) //Si el contador es 50
        {
            tem = temsum / 50;  //Divide la suma entre 50
            sprintf(lista, "%u", tem/2); //Crea lista con la temperatura 2bit x Grado
            puts(lista);    //Envia la temperatura por el puerto serie
            c = 0;  //Reinicia el contador
            temsum = 0; //Reinicia el sumador
        }
        __delay_ms(10);
    }
}
