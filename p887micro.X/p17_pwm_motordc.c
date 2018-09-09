/* Programa ejemplo para uso del ECCP como full-bridge con L298
 * Objetivo: Controlar el sentido de giro y velocidad de un motor DC
 * utilizando un POT para el comando conectado a RA0/AN0
 * Se utilizan los pines RD7(P1D) forward, RD5(P1B) back
 */
#pragma config FOSC=INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#define _XTAL_FREQ 8000000
#include <xc.h>
#include <stdlib.h>
#include "peripheral.h"
unsigned int adval;
void MotorAdelante();
void MotorReversa();
void CCPSetduty(unsigned n);
void CCPSetupPWM1();

void main(void) 
{
    OSCSetup();
    ANSEL = 0;
    ANSELH = 0;
    ANSELbits.ANS0 = 1; //Configura el pin AN0 como entrada
    TRISD = 0;
    TRISC = 0;
    TRISEbits.TRISE2 = 0;
    ADCSetup(); //Prepara el modulo ADC
    CCPSetupPWM1(); //Prepara el modo PWM
    while(1)
    {
        ADCStart(0);    //Inicia captura del canal 0
        __delay_us(20); //Espera requerida para completar la captura
        adval = ADCRead();//Lee el valor ADC(valor entre 0-1023)
        if(adval >= 512) //Control a la mitad del POT para adelante
        {
            adval = adval - 512;
            adval = adval * 2;
            if(adval > 1023) adval = 1023; //El valor no debe superar los 10bits.
            MotorAdelante();
        }
        else    //Control a la mitad del POT para atras
        {
            adval = 512 - adval;
            adval = adval * 2;
            if(adval > 1023) adval = 1023; //El valor no puede superar los 10bits
            MotorReversa();
        }
        CCPSetduty(adval); //Ajusta el ciclo de trabajo
        PORTEbits.RE2 = 0;
        __delay_ms(100);
        PORTEbits.RE2 = 1;
        __delay_ms(100);
    }
}
void MotorAdelante()
{
    TRISDbits.TRISD5 = 1;   //Deshabilita pin CCPx P1B
    TRISDbits.TRISD7 = 1;   //Deshabilita pin CCPx P1D
    PIR1bits.TMR2IF = 0;    //Limpia la bandera
    CCP1CONbits.P1M = 1;    //0 = Single, 1=Forward, 2=Half, 3=Back
    while(PIR1bits.TMR2IF == 0);//Espera un nuevo ciclo
    TRISDbits.TRISD5 = 0;   //Habilita pin CCPx P1B
    TRISDbits.TRISD7 = 0;   //Habilita pin CCPx P1D
}
void MotorReversa()
{
    TRISDbits.TRISD5 = 1;   //Deshabilita pin CCPx P1B
    TRISDbits.TRISD7 = 1;   //Deshabilita pin CCPx P1D
    PIR1bits.TMR2IF = 0;    //Limpia la bandera
    CCP1CONbits.P1M = 3;    //0 = Single, 1=Forward, 2=Half, 3=Back
    while(PIR1bits.TMR2IF == 0);//Espera un nuevo ciclo
    TRISDbits.TRISD5 = 0;   //Habilita pin CCPx P1B
    TRISDbits.TRISD7 = 0;   //Habilita pin CCPx P1D
}
void CCPSetupPWM1() //Frecuencia aproximada de 1KHz
{
    TRISDbits.TRISD5 = 1;   //Deshabilita pin CCPx P1B
    TRISDbits.TRISD7 = 1;   //Deshabilita pin CCPx P1D
    PIR1bits.TMR2IF = 0;    //Limpia la bandera
    CCP1CONbits.CCP1M = 0b1100; //P1A-P1C=ActiveHigh P1B-P1D=ActiveHigh
    CCP1CONbits.P1M = 3;//0 = Single, 1=Forward, 2=Half, 3=Back
    //Resolucion = log(4*(PR2+1))/log(2), si PR2=255 (10bit)
    PR2 = 255;  //10bit PWM(T) = [(PR2+1) * 4 * T2CKPS] / Fosc, es 1.02ms
    T2CONbits.T2CKPS = 0; //Prescala 0 = 1:1, 1 = 1:4, 2 = 1:16
    T2CONbits.TMR2ON = 1;   //Arranca el Timer   
    while(PIR1bits.TMR2IF == 0);//Espera un nuevo ciclo
    TRISDbits.TRISD5 = 0;   //pin CCPx P1B
    TRISDbits.TRISD7 = 0;   //pin CCPx P1D
}
void CCPSetduty(unsigned int n) //0-1023
{
    CCPR1L = n >> 2;        //Carga los 8-bits MSB del ciclo
    CCP1CONbits.DC1B = n;   //Carga los 2-bits LSB del ciclo
    PIR1bits.TMR2IF = 0;
}
