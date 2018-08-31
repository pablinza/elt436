/*Programa para manejar el modulo usart del PIC16F
 * Objetivo: Conectar un pulsador al pin RB0 y enviar un dato byte 
 * por el puerto serie con el valor del estado logico, ademas se
 * debe configurar la recepcion de un dato byte y representar su 
 * estado en un led conectado al pin RC0
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "peripheral.h"
char recbyte; //Variable para leer byte recibido por UART
char pinval = 1; //Variable para guardar el estado del pulsador

void main()
{
    OSCSetup(); //Este procedimiento ajusta el oscilador interno a la frecuencia
    ANSEL = 0;
    ANSELH = 0;
    TRISBbits.TRISB0 = 1;//Configura como entrada el pin RB0 
    TRISCbits.TRISC0 = 0;//Configura como salida el pin RC0
    PORTCbits.RC0 = 0;  //Coloca en 0 el pin RC0 
    OPTION_REGbits.nRBPU = 0;   //Activa las pull-ups del PORTB
    USARTSetup(9600);    //Configura el UART a 9600bps
    while(1)
    {
        if(PORTBbits.RB0 != pinval)  //Verifica si pulsador es presionado
        {
            pinval = !pinval;	//cambia el estado de la variable
            if(pinval == 1)		//Si el valor de val es 1 
                putch('1');		//Envia el byte ascii '1'
            else
                putch('0');		//Envia el byte ascii '0'
        }
        if(PIR1bits.RCIF == 1)	//Verifica si hay un dato byte listo para leer
        {
            recbyte = getch();	//Recibe el byte y lo guarda en una variable
            if(recbyte == '1')	//Verifica si el byte es ascii '1'
                PORTCbits.RC0 = 1;	//Enciende el LED
            if(recbyte == '0')	
                PORTCbits.RC0 = 0;	//Apaga el LED
        }
        USARTCheck();	//Este procedimiento verifica y limpia posibles errores de UART
        __delay_ms(10);
    }
    
}
