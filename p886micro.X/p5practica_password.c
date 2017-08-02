/* Programa para manejar los puertos entrada y salida digital
 * Manejo del teclado KEYPAD con modulo LCD 
 * Capturar una secuencia de 4 caracteres y compara con la
 * clave "1234", si es identica muestra el mensaje "CORRECTO".
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdio.h>
#include <string.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define LCD_TRIS TRISC
#define LCD_PORT PORTC
#define LCD_RS PORTCbits.RC4 
#define LCD_EN PORTCbits.RC5
#include "lcd.h"
#define KB_PORT PORTB
#define KB_TRIS TRISB
#include "keypad.h"
char val, key, pass[8], passidx = 0;
void main()
{
    OSCSetup();
    ANSEL = 0;
    ANSELH = 0; //ANS8-13
    TRISC = 0;
    LCDSetup(LINES2);
    LCDPuts("PASS:");
    LCDSet(DON & CURSOR_OFF & BLINK_ON);// Display ON/Blink ON
    KBSetup();
    EnablePU();
    LCDGoto(0x40);
    while(true)
    {
        val = KBScan();
        if(val != 0)
        {
            key = KBGetchar(val);
            if(key == '*')
            {
                pass[passidx] = 0;//
                passidx = 0;//
                if(strcmp(pass, "1234") == 0) //
                {
                    LCDGoto(0x40);//
                    LCDPuts("CORRECTO");//
                    delayms(2000);//
                }
                LCDGoto(0x40);
                LCDPuts("     ");
                LCDGoto(0x40);
            }
            else
            {
                LCDPutc(key);
                pass[passidx] = key;//
                passidx ++;//
            }
            delayms(50);
        }
        delayms(20);
    }
}