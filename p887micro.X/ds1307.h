/*********************************************************
 *  Libreria RTC para el chip DS1307 por I2C
 *  Autor: Pablo Zarate email:pablo@digital-bo.com
 *  facebook group: ELECTRONICA MCU 
 *  Material de uso para aprendizaje en ELT436 U.E.B.
 * 	Requiere libreria I2C Addr: 0100xxxR/W
 *  PIN Mapping SDA=PIN5 SCL=PIN6 I2C for 100KHz Only
 *******************************************************************************/
// DOM-IGNORE-BEGIN
/*******************************************************************************
Derechos de Autor PCZ pablinza@me.com.
Se autoriza el uso, copia y distribucion de este software con fines educativos

Favor tomar en cuenta lo siguiente:
El software y documentacion provisto no implica garantia alguna en cuanto al uso 
y sus posibles resultados directos o indirectos, incluyendo posibles incidentes, 
daños personales, daños materiales, perdida de informacion, etc.
*******************************************************************************/
#define REG_SECONDS  0x00
#define REG_MINUTES  0x01
#define REG_HOURS    0x02
#define REG_DAY      0x03
#define REG_DATE     0x04
#define REG_MONTH    0x05
#define REG_YEAR     0x06
#define REG_CONTROL  0x07
#define REG_RAMINI   0x08
#define REG_RAMEND   0x3F
#define OSCOFF       0x00 //bit4=0(SQWE) bit0:1=00(RS) No Osc output
#define OSC1HZ       0x10 //bit4=1(SQWE) bit0:1=00(RS) 1Hz
#define OSC4KHZ      0x11 //bit4=1(SQWE) bit0:1=01(RS) 4.096Hz
#define OSC8KHZ      0x12 //bit4=1(SQWE) bit0:1=10(RS) 8.192Hz
#define OSC32KHZ     0x13 //bit4=1(SQWE) bit0:1=11(RS) 32.768Hz

#ifndef RTCADDR
#define RTCADDR 0b11010000  //DS1307 Default Address
#endif
char BCDtoDec(char val);
char DectoBCD(char val);
char RTCRead(char addr);    //Lectura de registro 00h-03Fh in BCD
void RTCWrite(char addr, char data);   //Escribe registro
void RTCSetup(char mode);   //Configuracion
#include "ds1307.c"

