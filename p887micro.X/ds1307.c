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
char BCDtoDec(char val)
{
    char res;
    res = (val & 0x0F) + ((val & 0xF0)>>4)*10;
    return res;
}
char DectoBCD (char val)
{
    char res;
    res = (val/10) << 4;
    res = res | (val % 10);
    return res;
}
char RTCRead(char addr)
{
    char data;
    I2CIdle();
    do
    {
        I2CStart();
    }   while(!I2CWrite(RTCADDR)); //Ack Received
    I2CWrite(addr);
    I2CIdle();
    I2CRestart();
    I2CWrite(RTCADDR | 1); //Wait for Read
    data = I2CRead(); //Read Second and CH = Bit7 Clock Halt
    I2CNotAck();
    I2CStop(); 
    return(data);
}
void RTCWrite(char addr, char data)
{
    I2CIdle();
    do
    {
        I2CStart();
    }   while(!I2CWrite(RTCADDR)); //Ack Received
    I2CWrite(addr);
    I2CWrite(data); //Force CH bit to 0 for disable Clock Halt
    I2CStop();
}
void RTCSetup(char mode)   //Configuracion
{
    char data;
    data = RTCRead(REG_SECONDS);
    data = data & 0x7F;
    RTCWrite(REG_SECONDS, data); //Force CH bit to 0 for disable Clock Halt
    RTCWrite(REG_CONTROL, mode); //OUT<b7> = 1 Enabled, RS<b0:1> = 00 1Hz
}

