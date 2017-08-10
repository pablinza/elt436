/* Uso de un Servomotor SG90 utilizando el modulo TIMER2
 * El control del servo esta conectado al pin RC0, y dos pulsadores
 * a los pines RB0 y RB1. El programa debe mover al servo en un angulo
 * positivo si se presionar RB0 y un angulo negativo si se presionar RB1
 * en caso de no presionar ningun boton el servo debe mantener una
 * posicion central 0.
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
bit ledstado;	//Configura bit de estado LED
#define BT0 PORTBbits.RB0 //Define el pin RB0 como BT0
#define BT1 PORTBbits.RB1 //Define el pin RB1 como BT1
void main()
{
    OSCSetup(); //Ajusta el oscilador interno a _XTAL_FREQ
    ANSEL = 0;	//Configura ANS0-7 en modo digital
    ANSELH = 0; //Configura ANS8-13 en modo digital
    TRISCbits.TRISC0 = 0; //Configura como salida el pin RC0
    PORTCbits.RC0 = off; //Apaga el led
    TMR2Setup(T2PRE16, T2POS5);//Ajusta la pre 1:16 y post 1:5 del timer2
    TMR2Setval(250); //Carga el valor de periodo al TIMER2 para 20ms
    TMR2Start(); //Inicia el temporizador
    while(1)
    {
        if(PIR1bits.TMR2IF == 1) //Si se cumplio el tiempo 20ms
        {
            if(BT0 == 1 && BT1 == 1) //Si BT0 y BT1 no estan presionados
            {
                PORTCbits.RC0 = 1;
                delayus(1500);		//Enviar un pulso de 1.5ms
                PORTCbits.RC0 = 0;
            }
            if(BT0 == 0 && BT1 ==1) //Si solo BT0 es presionado
            {
                PORTCbits.RC0 = 1;
                delayus(2000);		//Envia pulso de 2ms (angulo positivo)
                PORTCbits.RC0 = 0;
            }
            if(BT1 == 0 && BT0 ==1) //Si solo BT1 es presionado
            {
                PORTCbits.RC0 = 1;
                delayus(1000);	//Envia pulso de 1ms (angulo negativo)
                PORTCbits.RC0 = 0;
            }
            PIR1bits.TMR2IF = 0; ///Limpia la bandera del TIMER2
        }
        
        
    }
}
