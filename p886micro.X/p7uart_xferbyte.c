/* En este ejemplo se utilizara el modulo usart para 
 * establecer una comunicacion asincrona para el envio y recepcion
 * de un dato byte. 
 * Envia '1' al presionar un pulsador y '0' cuando no se presiona
 * Recibe un byte y si el valor es '1' enciende el led caso contrario
 * apaga el led conectado al pin RC0
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define SW1pin PORTBbits.RB0 //Pulsador de entrada
#define LEDpin PORTCbits.RC0 //Led de salida
bit SW1st;  //declara una variable de estado para el pulsador
char data;  //declara un variable para el dato byte recibido
void main()
{
    OSCSetup(); //Ajusta el oscilador interno a _XTAL_FREQ
    ANSEL = 0;  //Configura los canales ANS0-7 como digital
    ANSELH = 0; //Configura los canales ANS8-13 como digital
    EnablePU(); //Activa las resistencia pull-up del PORTB
    TRISBbits.TRISB0 = 1; //Configura el pin RB0 como entrada
    TRISCbits.TRISC0 = 0; //Configura el pin RC0 como salida
    UARTSetup(9600);    //Configura el modulo USART
    SW1st = SW1pin;     //Inicia el valor de la variable de estado
    printf("LISTO\r\n");    //Envia un mensaje por el puerto UART
    while(true)
    {
        if(SW1st != SW1pin) //Si pulsador cambia de esto con respecto al variable
        {
            SW1st = SW1pin; //Variable se carga con el estado del pulsador
            printf("%u", SW1st); //Envia el valor '0' o '1' del pulsador
            delayms(50);    //retardo 
        }
        if(PIR1bits.RCIF == 1) //Si existe un dato listo en el UART
        {
            data = getchar();   //Lee el dato en la variable 
            if(data == '1') //Si la variable es '0'
                LEDpin = 1; //Activa el led
            else    //Caso contrario
                LEDpin = 0; //Apaga el led
        }
    
    }
}
