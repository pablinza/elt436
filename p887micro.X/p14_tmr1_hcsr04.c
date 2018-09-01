/*  Programa para manejar un sensor de distancia HC-SR04 
 * Objetivo: Realizar un programa que mida la distancia en cm
 * y envie el valor como un mensaje por usart cada segundo
 *  RD0=Trig RD1=Echo */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#define TRIGpin PORTDbits.RD0
#define ECHOpin PORTDbits.RD1
#include "peripheral.h"
unsigned int distcm = 0;
unsigned int SR04Getval();
void DelayMS(unsigned int n);
void main(void)
{
    ANSEL = 0;	//AN0-AN7 en modo digital
    ANSELH = 0;	//AN8-AN12 en modo digital
    TRISEbits.TRISE2 = 0; //Led pin RE2
    TRISDbits.TRISD0 = 0; //Trig
    TRISDbits.TRISD1 = 1; //Echo
    PORTD = 0;
    UARTSetup(9600);    //Configura el modulo Serial
    TMR1Setup(TIMER, T1PRE1); //1uS 
    TMR0Setup(TIMER, T0PRE8); //1uS PRE8 = 8uS
    while(1)
    {
        distcm = SR04Getval();
        printf("Distancia cm:%u\r\n", distcm);
        DelayMS(500);
        PORTEbits.RE2 = 0;
        DelayMS(500);
        PORTEbits.RE2 = 1;
    }
}
void DelayMS(unsigned int n)
{
    while(n > 0)
    {
        TMR0Setval(131); //For 1ms Tcy=1uS PRE8
        INTCONbits.TMR0IF = 0;
        while(INTCONbits.TMR0IF == 0);
        n--;
    }
}
unsigned int SR04Getval()
{
    unsigned int value;
    TRIGpin = 1;
    __delay_us(10);
    TRIGpin = 0;
    while(ECHOpin == 0);
    PIR1bits.TMR1IF = 0;
    TMR1Setval(0);
    TMR1Start();
    while(ECHOpin == 1)
    {
        if(PIR1bits.TMR1IF == 1)
            break;
    }
    TMR1Stop();
    value = TMR1Getval();
    //vs= 343m/s => 0.0343 cm/uS => 0.343 mm/uS => 1mm/3uS => 1cm/30uS
    //2 x dist = (tcy x pre) x 1cm/30uS
    return value/60;
}
