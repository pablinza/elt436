/* Programa de prueba para control Servo 
 * conectado al pin RC1 Modulo CCP2 
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
unsigned int val;
void main()
{
    OSCSetup(); //Ajusta el oscilador interno a _XTAL_FREQ
    ANSEL = 0; //Configura el ANS0-7 como digital
    ANSELH = 0; //Configura el ANS8-13 como digital
    ANSELbits.ANS0 = 1; //Configura ANS0 en modo analogico
    CCP2Setup(PWM); //Configura el modulo CCP2
    PWM2Setduty(500); //Establece el ciclo de trabajo en aprox. 50%
    PWMSetperiod(250, T2PRE4); //Ajusta el periodo para 1kHz 0.001s
    ADCSetup();//Configura el modulo ADC
    while(true)
    {
        delayms(100); //retardo
        val = ADCRead(0); //Lee el valor de POT
        PWM1Setduty(val); //Ajusta el ciclo de trabajo con el POT
    }
}
