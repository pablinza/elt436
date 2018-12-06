/************************************************************************
* Libreria de rutinas basicas para los Recursos/Perifericos de los MCU	*
* 				PIC12F   					 			   				* 
*    Company: Universidad Evangelica Boliviana 							*
*     Author: Pablo Zarate A. pablinza@me.com							*
*    Version: Dec  2018 V18.12  										*
*    Summary: Es una libreria de funciones y procedimientos de uso base *
*			  para los PIC serie 16F68x empleados en la materia ELT-436.*
************************************************************************/
#if !defined(_12F629) && !defined(_12F675) 
	#error "Libreria rutinas.c no corresponde al PIC seleccionado"
#endif
#ifndef _XTAL_FREQ
	#error "Debe definir la frecuencia de operacion _XTAL_FREQ"
#endif
#define true 1
#define false 0
#define EnablePU() OPTION_REGbits.nGPPU = 0 //Activa las pullups
/************************************************
 * 				Modulo EEPROM					*
 ************************************************/
void EEWrite(char addr, char data); //Escribe una byte en memoria EEPROM
char EERead(char addr);				//Lee un byte de la memoria EEPROM

/************************************************
 * 			Modulo Conversor ADC				*
 ************************************************/
#ifdef _12F675
void ADCSetup(); 
unsigned int ADCRead(char ch);
#endif
/************************************************
 * 			Modulo TIMER0           			*
 ************************************************/
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
void TMR0Setup(char cs, char pre);
#define TMR0Setval(x) TMR0 = x
char TMR0Getval();
/********************************************
 * 			Modulo TIMER1					*
 ********************************************/
#define T1PRE8 3
#define T1PRE4 2
#define T1PRE2 1
#define T1PRE1 0
void TMR1Setup(char cs, char pre);
#define TMR1Start() T1CONbits.TMR1ON = 1
#define TMR1Stop() T1CONbits.TMR1ON = 0
#define TMR1Setval(x) {TMR1L = x; TMR1H = x >> 8;}
unsigned int TMR1Getval();
#include "peripheral.c"
