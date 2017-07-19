/************************************************************************
* Libreria de rutinas basicas para los PIC16F882/F883/F884/F886/F887    * 
*    Company: Universidad Evangelica Boliviana 							*
*     Author: Pablo Zarate A. pablinza@me.com							*
*    Version: Julio 2017 V17.7  										*
*    Summary: Es una libreria de funciones y procedimientos de uso base *
*			  para los PIC serie 16F88x empleados en la materia ELT-436.*
************************************************************************/
#if !defined(_16F882) && !defined(_16F884) && !defined(_16F886) && !defined(_16F887)
	#error "Libreria rutinas.c no corresponde al PIC seleccionado"
#endif
#ifndef _XTAL_FREQ
	#error "Debe definir la frecuencia de operacion _XTAL_FREQ"
#endif
#define true 1
#define false 0
#define on 1
#define off 0
#define up 1
#define down 0
#define delayms __delay_ms
#define delayus __delay_us
#define delay __delay
#define EnablePU() OPTION_REGbits.nRBPU = 0 //Activa las pullups del PORTB
/************************************************
 * 				Modulo OSCILADOR				*
 ************************************************/
void OSCSetup();//Ajusta el oscilador interno a _XTAL_FREQ

/************************************************
 * 				Modulo USART					*
 ************************************************/
#define getche getch
void UARTSetup(unsigned int baud);//Inicia y configura la velocidad
void UARTCheck();//Verifica si hay errores y reinicia el receptor
void putch(char byte);//Envia un byte por el modulo USART
char getch();//Recibe un byte del modulo USART

/************************************************
 * 				Modulo EEPROM					*
 ************************************************/
void EEWrite(char addr, char data); //Escribe una byte en memoria EEPROM
char EERead(char addr);//Lee un byte de la memoria EEPROM

/************************************************
 * 			Modulo Conversor ADC				*
 ************************************************/
void ADCSetup(); 
unsigned int ADCRead(char ch);
/************************************************
 * 				Modulo TIMER0					*
 ***********************************************/
#define COUNTER 1
#define TIMER 0
#define T0PRE256 7
#define T0PRE128 6
#define T0PRE64 5
#define T0PRE32 4
#define T0PRE16 3
#define T0PRE8 2
#define T0PRE4 1
#define T0PRE2 0
#define T0PRE1 8
#define TMR0Setpulse(x) OPTION_REGbits.T0SE = !x
void TMR0Setup(char cs, char pre); //Ajusta el modo TIMER/COUNTER y la preescala T0PRE1 - T0PRE256
char TMR0Getval();
void TMR0Setval(char value); //Carga el registro TMR0 y limpia la bandera
/************************************************
 * 				Modulo TIMER1					*
 ***********************************************/
#define T1PRE1 0
#define T1PRE2 1
#define T1PRE4 2
#define T1PRE8 3
#define TMR1Start() T1CONbits.TMR1ON = 1
#define TMR1Stop() T1CONbits.TMR1ON = 0
void TMR1Setup(char cs, char pre);//Ajusta el modo TIMER/COUNTER y la preescala T1PRE1 - T1PRE8
void TMR1Setval(unsigned int value);//Carga el registro TMR1 y limpia la bandera
unsigned int TMR1Getval();
 /************************************************
 * 				Modulo TIMER2					*
 ***********************************************/
#define T2PRE1 0
#define T2PRE4 1
#define T2PRE16 2
#define T2POS1 0
#define T2POS2 1
#define T2POS3 2
#define T2POS4 3
#define T2POS5 4
#define T2POS6 5
#define T2POS7 6
#define T2POS8 7
#define T2POS9 8
#define T2POS10 9
#define T2POS11 10
#define T2POS12 11
#define T2POS13 12
#define T2POS14 13
#define T2POS15 14
#define T2POS16 15
#define TMR2Start() T2CONbits.TMR2ON = 1
#define TMR2Stop() T2CONbits.TMR2ON = 0
void TMR2Setup(char pre, char post);
void TMR2Setval(char value);
char TMR2Getval();
/************************************************
 *				Modulo de CCPx					*	
 ************************************************/
#define CCPOFF 0
#define PWM 0b1100  //Mode PWM
void CCP1Setup(char mode);
void CCP2Setup(char mode);
void PWMSetperiod(char period, char pre); //x10uS 1000
void PWM1Setduty(unsigned short mod);
void PWM2Setduty(unsigned short mod); //10bit

#include "rutinas.c"
