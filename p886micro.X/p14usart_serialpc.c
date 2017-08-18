/* Programa utilizando el puerto USART del PIC para la comunicacion
 * serial con una Aplicacion de PC. muestra el envio y recepcion de 
 * estado para dos led y dos pulsadores
 */
#pragma config FOSC=INTRC_NOCLKOUT, WDTE=OFF,LVP=OFF
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define LED1 PORTCbits.RC0
#define LED2 PORTCbits.RC1
#define BT1 PORTBbits.RB0
#define BT2 PORTBbits.RB1
bit bt1estado, bt2estado;
char val;
void main()
{
    OSCSetup();
    ANSEL = 0;
    ANSELH = 0;
    TRISCbits.TRISC0 = 0;//modo salida LED1
    TRISCbits.TRISC1 = 0; //modo salida LED2
    EnablePU();
    LED1 = off; //Apaga el LED1
    LED2 = off; //Apaga el LED2
    UARTSetup(9600);
    while(1)
    {
        if(BT1 != bt1estado)
        {
            bt1estado = BT1;
            if(bt1estado == 0)
                putchar('1'); //Si Boton1 es presionado envia '1'
            else
                putchar('0'); //Si Boton1 no esta presionado envia '0'
        }
        if(BT2 != bt2estado)
        {
            bt2estado = BT2;
            if(bt2estado == 0)
                putchar('3'); //Si Boton2 es presionado envia '1'
            else
                putchar('2'); //Si Boton2 no esta presionado envia '0'
        }
        if(PIR1bits.RCIF)
        {
            val = getchar();
            if(val == '1') //Si dato recibido es '1' activa LED1
                LED1 = on;
            if(val == '0') //Si dato recibido es '0' apaga LED1
                LED1 = off;
            if(val == '2') //Si dato recibido es '2' activa LED2
                LED2 = on;
            if(val == '3') //Si dato recibido es '3' apaga LED2
                LED2 = off;             
        }
    }
}
