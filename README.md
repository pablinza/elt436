# B8P40 Microcontrolador PIC16F887
Descripcion de la Placa B8P40 utilizada para los ejercico de programacion en Laboratorio U.E.B Asignatura ELT
<p align="center">
  <img src="/images/b8p40.png"></img>
</p>
Lista de Repositorio de practicas efectuadas en laboratorio <br />
- https:/github.com/pablinza/piclab1.git <br />
- https:/github.com/pablinza/piclab2.git (en desarrollo) <br />

## ESQUEMAS DEL CIRCUITO ELECTRONICO
### - BLoque 1 - Conexiones del Microcontrolador
  <p align="center">
  <img src="/images/b8p40_sch_p1.png"></img>
</p>

### - BLoque 2 - Elementos Adicionales de la Tarjeta
<p align="center">
  <img src="/images/b8p40_sch_p2.png"></img>
</p>

## Programa para destellar el LED 
El siguiente codigo es un ejemplo basico creado en MPLABX el cual permite destellar el LED  DS1 conectado el pin RE2 del MCU, este codigo sera la base del resto de ejemplo que se veran en los laboratorios. En el codigo se considera que el PIC16F887 opera a una frecuencia de 8MHz utilizando el Oscilador Interno. En caso de utilizar tinybootloader, se debe reservar el uso de memoria en MPLABX.
La carpeta `p0apptest.X` coeesponde al proyecto generado con `MPLABX` version 6.25 y utiliza el compilador `XC8` version 2.5 <br />
La carpeta `P0apptestasm.X` contiene el proyecto generado con `MPLABX` version 6.25 utilizando el ensamblador `PIC-AS` <br />
ent level
- Codigo del programa en `main c` 
```c
#pragma config FOSC=INTRC_NOCLKOUT, WDTE = OFF, BOREN = OFF, LVP = OFF
#include <xc.h>
#define LEDpin PORTEbits.RE2 //Led de la tarjeta
volatile __bit tickms;
void setupMCU(void); //Configuracion del PIC
void taskLED(void); //Tarea para destellar el LED
void __interrupt() isr(void) //Rutina de servicio a la Interrupcion
{
    if(INTCONbits.T0IF) //Evento del temporizador 0.001s
    {
        INTCONbits.T0IF = 0;
        TMR0 += 131; //Recarga el contador
        tickms = 1;
    }
}
void main(void) 
{
    setupMCU();
    while(1)
    {
        if(tickms)
        {
            tickms = 0;
            taskLED(); //Destella LED
        }
    }
}
void setupMCU(void)
{
    OSCCONbits.IRCF = 0b111; //Oscilador Interno 8MHz
    while(OSCCONbits.HTS == 0);
    ANSEL = 0; //Desactiva pines ADC AN0 al AN7
    ANSELH = 0;//Desactiva pines ADC AN8 al AN13
    TRISEbits.TRISE2 = 0; //Salida LED
    OPTION_REGbits.nRBPU = 0; //Activa las pull-ups PORTB
    /* CONFIGURACION TIMER0 1MS a Fosc=8MHz*/
    OPTION_REGbits.T0CS = 0;//Modo Termporizador
    OPTION_REGbits.PSA = 0; //Con prescala
    OPTION_REGbits.PS = 0b011; //Prescala 1:16
    TMR0 = 131; //256-(time/((pre)*(4/Fosc))) time=0.001 seg
    INTCONbits.T0IF = 0; //Limpia bandera
    INTCONbits.T0IE = 1; //Activa interrupcion del TMR0
    
    INTCONbits.GIE = 1; //Habilitador global ISR
}
void taskLED(void) //Destello de LED1 1Hz al 20%
{
    static uint16_t cnt = 0;
    if(cnt++ > 999) 
    {
        cnt = 0;
        LEDpin = 1; //Activa LED
    }
    if(cnt == 200) LEDpin = 0; //Apaga LED
}
```

Adjunto el siguiente link que muestra como compilar estos ejemplos en MPLABX
[![](http://img.youtube.com/vi/w-GRu89glrg/0.jpg)](http://www.youtube.com/watch?v=w-GRu89glrg "Compilar en MPLABX")

<img src="pablo_ueb.png" align="left" width="200px"/>
Autor: Pablo Zarate, puedes contactarme a pablinza@me.com / pablinzte@gmail.com.  <br />
Visita mi Blog  [Blog de Contenidos](https://pablinza.blogspot.com/). <br />
Visita mi Canal [Blog de Contenidos](http://www.youtube.com/@pablozarate7524)). <br />
Facultad de Ciencias y Tecnologia UEB - Ingenieria Electronica. <br />
Santa Cruz - Bolivia 
<br clear="left"/>
***********************

