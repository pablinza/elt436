/*Ejemplo de uso del HC-SR04, utilizando el TIMER0 como contador de uS
 con la prescala asignada de 1:16 se tiene una cuenta maxima de 
 16uS x 256 = 4096uS, esto nos da una distancia maxima de 4096/58 = 70cm*/
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF, MCLRE = OFF
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include "rutinas.h"
#define TRIGpin PORTCbits.RC0 //define el pin para disparo Trigger SR04
#define ECHOpin PORTCbits.RC1 //define el pin del Eco SR04
char cont, distcm;
void main(void) 
{
    OSCSetup(); //Ajusta el oscilador interno a _XTAL_FREQ
    TRISCbits.TRISC0 = 0; //Configura el Trigger como salida
    TRISCbits.TRISC1 = 1; //Configura el Echo como entrada
    TMR0Setup(TIMER, T0PRE16); //Ajusta en modo temporizador con pre de 1:16
    UARTSetup(9600); //Configura el usart a 9600 baudios
    while(1)
    {
        TRIGpin = up; //Inicia el pulso del disparo Trigger
        delayus(10);//espera
        TRIGpin = down;//Finaliza el pulso del disparo
        while(PORTCbits.RC1 == 0);//Espera el inicio del Eco
        TMR0Setval(0);//Inicia el temporizador
        while(PORTCbits.RC1 == 1);//Espera el final del Eco
        cont = TMR0Getval();
        distcm = cont * 16/58; //16us 1cm/58uS
        printf("dist:%u\n",distcm);
        delayms(1000);
    }
}
/* Un programa mas real, debe implicar maximos de espera que puedan finalizar
 los bucles while utilizados para la respuesta ECHO, ademas se debe considerar 
 el desbordamiento por espera del TMR0*/

