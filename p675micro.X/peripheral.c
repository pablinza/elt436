/************************************************************************
* Libreria de rutinas basicas para los Recursos/Perifericos de los MCU	*
* 				PIC16F687/F689/F690 			   				* 
*    Company: Universidad Evangelica Boliviana 							*
*     Author: Pablo Zarate A. pablinza@me.com							*
*    Version: Julio 2018 V18.7  										*
*    Summary: Es una libreria de funciones y procedimientos de uso base *
*			  para los PIC serie 16F68x empleados en la materia ELT-436.*
************************************************************************/
void EEWrite(char addr, char data)
{
    char GIEbit;
    EEADR = addr;
    EEDAT = data;
    EECON1bits.WREN = 1;
    GIEbit = INTCONbits.GIE;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while(EECON1bits.WR);
    INTCONbits.GIE = GIEbit;
    EECON1bits.WREN = 0;
}
char EERead(char addr)
{
    EEADR = addr;
    EECON1bits.RD = 1;
    return EEDAT;
}
#ifdef _12F675
void ADCSetup()
{
    ANSELbits.ADCS = 0b011; //Ajusta el TAD a FRC
    ADCON0bits.VCFG = 0; //0=VDD    1=RA1/Vref
    ADCON0bits.ADON = 1;
}
unsigned int ADCRead(char ch)
{
    unsigned int value;
    ADCON0bits.CHS = ch;
    _delay(20); //2TAD
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    value = ADRESH;
    value = (value << 8) & 0xFF00;
    value = value | ADRESL;
    value = value >> 6;
    return value;
}
#endif
void TMR0Setup(char cs, char pre)
{
    OPTION_REGbits.T0CS = cs;
    OPTION_REGbits.T0SE = 0; //Counter 0=rising 1=falling
    if(pre < 8)
    {    
        OPTION_REGbits.PSA = 0;
        OPTION_REGbits.PS = pre;
    }
    TMR0 = 0;
    INTCONbits.T0IF = 0;
}
char TMR0Getval()
{
    return TMR0;
}
void TMR1Setup(char cs, char pre)
{
    T1CONbits.TMR1CS = cs;
    T1CONbits.T1CKPS = pre;
    TMR1H = 0;
    TMR1L = 0;
    PIR1bits.TMR1IF = 0;
}
void TMR1Setval(unsigned int value)
{
    TMR1L = value;
    TMR1H = (char) value >> 8;
}
unsigned int TMR1Getval()
{
    unsigned int value;
    value = TMR1H;
    value = value << 8;
    value |= TMR1L; 
    return value;
}