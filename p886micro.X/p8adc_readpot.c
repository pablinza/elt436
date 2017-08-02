/* En este ejemplo se utilizara el modulo ADC para la lectura 
 * Conectar un potenciometro de 10k en el pin RA2/AN2, hacer la lectura ADC
 * e imprimir el valor digital, si el voltaje es menor a 1V activar un led
 * conectado al pin RB1, si el voltaje es mayor a 4V activar un led conectado
 * al pin RB0.
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define LED2pin PORTBbits.RB0   //Define el led de salida RB0
#define LED1pin PORTBbits.RB1   //Define el led de salida RB1
unsigned int adval; //Variable para la conversion
void main()
{
    OSCSetup(); //Ajusta el oscilador a _XTAL_FREQ
    ANSEL = 0;  //Configura ANS0-7 en modo digital
    ANSELH = 0; //Configura ANS8-13 en modo digital
    ANSELbits.ANS2 = 1; //Activa el pin ANS2 en modo analogico
    TRISBbits.TRISB0 = 0;   //Configura el pin RB0 como salida
    TRISBbits.TRISB1 = 0;   //Configura el pin RB1 como salida
    UARTSetup(9600); //Ajusta a 9600
    ADCSetup(); //Configura el convertidor ADC
    while(true)
    {
        adval = ADCRead(2); //Captura la conversion del canal2
        if(adval < 200) //Si el valor es menor a 1V. (200 digital)
            LED1pin = 1;    //Activa el led RB1
        else
            LED1pin = 0;    //Caso contrario apaga el led RB1
        if(adval > 800) //Si el valor es mayor a 4V.(800 digital)
            LED2pin = 1;    //Activa el led RB0
        else
            LED2pin = 0; //Caso contrario apaga el led RB0
        printf("V:%s\r", adval);    //Muestra el valor de conversion.
        delayms(1000);  //Retardo de 1seg.
    }
}
