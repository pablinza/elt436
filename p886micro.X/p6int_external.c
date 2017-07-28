/*  Programa para la practica de la materia ELT436 de la U.E.B
 * Manejo de la interrupcion externa con la rutina isr del PIC
 * El programa destella un led1 conectado al pin RC0 cada 0.5seg
 * Detecta si el pulsador conectado al pin RB0 es presionado y 
 * activa un segundo led conectado al pin RC1 por 5 segundos. 
*/
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
bit evt1 = 0;   //declara una variable bit para evento isr
char cont = 0;  //declara un contador con valor inicial 0

void interrupt isr()    //Servicio de rutina de interrupcion.
{
    if(INTCONbits.INTF == 1) //Verifica bandera interrupcion ext.
    {
        evt1 = 1;   //Activa bandera de evento isr
        INTCONbits.INTF = 0; //limpia la bandera de interrupcion ext
    }
} //retorna al bucle principal

void main() //Programa principal
{
    OSCSetup(); //Ajusta el oscilador interno a la _XTAL_FREQ
    ANSEL = 0; //Configura los pines ANS0-ANS7 en modo digital
    ANSELH = 0; //Configura los pines ANS8-ANS13 en modo digital
    TRISCbits.TRISC0 = 0; //Configura Salida led1
    TRISCbits.TRISC1 = 0; //Configura Salida led2
    TRISBbits.TRISB0 = 1; //Configura Entrada pulsador
    EnablePU(); //Activa las resistencias pullup del PORTB
    INTCONbits.INTE = 1; //Habilita interrupcion externa RB0
    INTCONbits.GIE = 1; //Activa las interrupciones
    while(1)
    {
        PORTCbits.RC0 = 0;  //Apaga el led RC0
        delayms(500);       //retardo medio segundo
        PORTCbits.RC0 = 1;  //Enciende el led RC0
        delayms(500);       //retardo medio segundo
        if(evt1 == 1)       //Verifica si bandera de evento esta activa
        {
            PORTCbits.RC1 = 1; //Activa el led RC1
            cont ++;    //Incrementa el contador (500ms + 500ms = 1seg)
            if(cont > 4)    //Verifica si el contador es mayor a 4( aprox. 5seg)
            {
                PORTCbits.RC1 = 0;  //Apaga el led RC1
                evt1 = 0;   //Limpia la bandera de evento
                cont = 0;   //Reinicia el contador
            }
        }
    }
}
