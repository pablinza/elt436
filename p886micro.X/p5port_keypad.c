/* Programa para manejar los puertos entrada y salida digital
 * Manejo del teclado KEYPAD con modulo LCD, se muestra la 
 * tecla presionada y se limpia la pantalla con 'D'
 */
#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#include <stdio.h>
#include <string.h>
#define _XTAL_FREQ 4000000
#include "rutinas.h"
#define LCD_TRIS TRISC  //Define el Registro de configuracion LCD
#define LCD_PORT PORTC  //Define el Puerto de datos LCD
#define LCD_RS PORTCbits.RC4 //Define el pin de control RS  
#define LCD_EN PORTCbits.RC5 //Define el pin de control EN
#include "lcd.h" //Agrega la libreria basica del LCD
#define KB_PORT PORTB   //Define el Puerto de datos para el PAD
#define KB_TRIS TRISB   //Define el Registro de configuracion PAD
#include "keypad.h"     //Agrega la libreria basica del PAD
char val, key, pass[8], passidx = 0;
void main()
{
    OSCSetup(); //Ajusta el oscialdor a _XTAL_FREQ
    ANSEL = 0;  //Coloca en modo digital los pines ANS0-7
    ANSELH = 0; //Coloca en modo digital los pines ANS8-13
    TRISC = 0;  //Configura el PORTC como salida
    PORTC = 0;  //Establece el valor inicial del PORTC
    LCDSetup(LINES2);   //Inicia el LCD con dos lineas
    LCDPuts("TECLADO:"); //Escribe en el LCD la palabra 
    LCDSet(DON & CURSOR_OFF & BLINK_ON);// Display ON/Blink ON
    KBSetup();  //Inicializa el Keypad
    EnablePU(); //Activa las resistencias pull-up del PORTB
    LCDGoto(0x40);  //Posiciona el cursor LCD en la segunda linea
    while(true)
    {
        val = KBScan(); //Hace una captura de PAD
        if(val != 0)    //Si el velor no es nulo
        {
            key = KBGetchar(val); //Recupera la tecla presionada
            if(key == 'D')        //Si la tecla presionada es 'D'
            {
                LCDSet(CLEAR);      // Limpia el display
                LCDGoto(0x00);      //Posiciona el cursor al inicio
                LCDPuts("TECLADO:");//Escribe en el LCD la palabra 
                LCDGoto(0x40);  //Posiciona el cursor en la segunda linea
            }
            else
                LCDPutc(key);   //Escribe el valor de la tecla en el LCD
            delayms(50);
        }
        delayms(20);
    }
}