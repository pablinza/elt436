/* Programa para manejar los puertos entrada y salida digital
 * Display de 7 Segmentos, montaje de 1er display para conversion vector
 * Montaje de segundo display de multiplexacion por tiempo
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF, MCLRE = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define DP1pin PORTAbits.RA0
#define DP2pin PORTAbits.RA1
#define DP3pin PORTAbits.RA2
char dmap[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
char n = 0, lsb=0, msb=0, dec=0, cnt = 0, debounce = 0;
bit sw1bit = 0;
void main()
{
    OSCSetup();
    ANSEL = 0;
    ANSELH = 0; //ANS8-13
    TRISC = 0; //Configura todos los bits del PORTC como salida
    TRISAbits.TRISA0 = 0; //Activa DP1
    TRISAbits.TRISA1 = 0; //Activa DP2
    TRISAbits.TRISA2 = 0; //Activa DP2
    EnablePU();
    PORTC = 0;
    PORTA = 0;
    while(true)
    {
        PORTC = dmap[dec];
        DP1pin = 1;
        delayms(3);
        DP1pin = 0;
        
        PORTC = dmap[lsb]; //
        PORTCbits.RC7 = 1;
        DP2pin = 1; //Activa el display 1
        delayms(3);
        DP2pin = 0; //Desactiva el display 1
        PORTCbits.RC7 = 0;
        
        PORTC = dmap[msb];
        DP3pin = 1; 
        delayms(3);
        DP3pin = 0; 
        delayms(1);
        if(sw1bit == 1)
        {
            n = n + 1;
            if(n > 9) //15ms x 66.6 =1sec
            {
                dec = dec + 1;
                if(dec > 9)
                {
                    cnt = cnt + 1;
                    if(cnt > 59) cnt = 0;    
                    msb = cnt / 10;
                    lsb = cnt % 10;
                    dec = 0;
                }
                n = 0;
            }
        }
        if(PORTBbits.RB0 == 0)  //presionado
        {
            debounce ++;
            if(debounce == 200) //10ms x 50 = 500ms
            {   
                msb = 0;
                lsb = 0;
                dec= 0;
                debounce = 0;
            }
        }
        else
        {
            if(debounce > 24)
                sw1bit = !sw1bit;
            debounce = 0;
        }
    }
}
/* CONCURSO QUIEN ARMA UN CRONOMETRO CON MM:SS:mil START, STOP, RESET*/