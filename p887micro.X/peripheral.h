/************************************************************************
* Libreria de rutinas basicas para los Recursos/Perifericos de los MCU	*
* 				PIC16F882/F883/F884/F886/F887 			   				* 
*    Company: Universidad Evangelica Boliviana 							*
*     Author: Pablo Zarate A. pablinza@me.com							*
*    Version: Julio 2018 V18.7  										*
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
#define EnablePU() OPTION_REGbits.nRBPU = 0 //Activa las pullups del PORTB
/************************************************
 * 				Modulo OSCILADOR				*
 ************************************************/
void OSCSetup();					//Ajusta el oscilador interno a _XTAL_FREQ

/************************************************
 * 				Modulo USART					*
 ************************************************/
#define getche getch
void UARTSetup(unsigned int baud);	//Inicia y configura la velocidad
void UARTCheck();					//Verifica si hay errores y reinicia el receptor
void putch(char byte);				//Envia un byte por el modulo USART
char getch();						//Recibe un byte del modulo USART

/************************************************
 * 				Modulo EEPROM					*
 ************************************************/
void EEWrite(char addr, char data); //Escribe una byte en memoria EEPROM
char EERead(char addr);				//Lee un byte de la memoria EEPROM

/************************************************
 * 			Modulo Conversor ADC				*
 ************************************************/
void ADCSetup(); 
unsigned int ADCRead(char ch);

#include "peripheral.c"
