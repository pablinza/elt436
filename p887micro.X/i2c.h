/*********************************************************
 *  Libreria I2C para el modulo MSSP/SSP PIC16F
 *  Autor: Pablo Zarate email:pablo@digital-bo.com
 *  facebook group: ELECTRONICA MCU 
 *  Material de uso para aprendizaje en ELT436 U.E.B.
 * 
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
#ifndef _XTAL_FREQ
    #error "Debe Definir la Frecuencia de Operacion"
#endif
#define I2CLOW 31
#define I2CSTD 100
#define I2CFAST 400
#define I2CHIGH 1000
void I2CSetup(unsigned int rate);
void I2CIdle();  //Test if I2C1 module is in idle
void I2CAck();   //Send ACK
void I2CNotAck();//Send NACK
void I2CStop();  //Send STOP
void I2CStart(); //Send START
void I2CRestart();//Send RESTART
char I2CRead();
char I2CWrite(char data);
#include "i2c.c"

