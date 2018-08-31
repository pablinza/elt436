/*Programa para manejo del puerto serie con USART 
 * Objetivo: Enviar un mensaje cada segundo con el valor de dos 
 * variables de conteo que se incrementan y al recibir un mensaje
 * "reset" deberan reiniciarse
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
char rxbuf[16]; //Lista o vector para recibir el mensaje
char bpos = 0;  //Variable para indicar la posicion en la lista
char byte, rxok = 0, res; //Variables de uso temporal 
unsigned int val1, val2; //Contadores
void interrupt isr()    //Rutina de interrupcion
{
    if(PIR1bits.RCIF == 1) //hay dato en la recepcion
    {
        byte = getch(); //Leer el byte que llego
        if(byte == '\n')    //Verificar si el dato es "newline"
        {
            rxbuf[bpos] = 0; //Coloca el byte nulo
            bpos = 0;   //Reinicia el indicador de posicion
            rxok = 1;   //Activa bandera de mensaje recibido
        }
        else    //Si el dato recibido no es "newline"
        {
            rxbuf[bpos] = byte; //Almacena el dato recibido en la lista
            bpos ++;    //incrementa la posicion
        }
    }
        
}
void main(void) //Funcion principal
{
    OSCSetup();
    ANSEL = 0;  //Configura los pines AN0-AN7 en modo digital
    ANSELH = 0; //Configura los pines AN8-AN15 en modo digital
    USARTSetup(9600);
    PIE1bits.RCIE = 1;  //Activa la interrupcion de recepcion USART
    INTCONbits.PEIE = 1;    //Activa la interrrupcion de perifericos
    INTCONbits.GIE = 1; //Activa la interrupcion global
    while(1)
    {
        val1 = val1 + 5;    //Incrementa val1 en 5
        if(val1 > 100)
            val1 = 0;
        val2 ++;        //Incrementa val2 
        if(val2 > 100)
        {
            val2 = 0;
        }  
        printf("%u,%u\n", val1, val2); //Envia el mensaje con los contadores
        __delay_ms(1000);   //Retardo de 1 segundo
        USARTCheck();    //Verifica y limpia errores de recepcion USART
        if(rxok == 1)   //Si hay un mensaje recibido
        {
            rxok = 0;   //Limpia la bandera
            res = strcmp(rxbuf, "reset");//Compara el mensaje
            if(res == 0)    //Si es "reset"
            {
                val1 = 0;   //Reinicia contador
                val2 = 0;
            }
        }
    }
}
