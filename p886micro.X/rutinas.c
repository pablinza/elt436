/************************************************************************
* Libreria de rutinas basicas para los PIC16F882/F883/F884/F886/F887    * 
*    Company: Universidad Evangelica Boliviana 							*
*     Author: Pablo Zarate A. pablinza@me.com							*
*    Version: Julio 2017 V17.7  										*
*    Summary: Es una libreria de funciones y procedimientos de uso base *
*			  para los PIC serie 16F88x empleados en la materia ELT-436.*
************************************************************************/
void OSCSetup()
{
#if _XTAL_FREQ == 8000000
    OSCCONbits.IRCF = 7;
#elif _XTAL_FREQ == 4000000
    OSCCONbits.IRCF = 6;
#elif _XTAL_FREQ == 2000000
    OSCCONbits.IRCF = 5;
#elif _XTAL_FREQ == 1000000
    OSCCONbits.IRCF = 4;
#elif _XTAL_FREQ == 500000
    OSCCONbits.IRCF = 3;
#elif _XTAL_FREQ == 250000
    OSCCONbits.IRCF = 2;
#elif _XTAL_FREQ == 125000
    OSCCONbits.IRCF = 1;
#elif _XTAL_FREQ == 31000
    OSCCONbits.IRCF = 0;
#else 
    #warning "Oscilador Interno no ajustado a Frecuencia"
#endif
#if _XTAL_FREQ < 125000
    while(!OSCCONbits.LTS);
#else
    while(!OSCCONbits.HTS);   
#endif
}
void UARTSetup(unsigned int baud)
{
    unsigned int brg;
    TXSTAbits.BRGH = 1;
    BAUDCTLbits.BRG16 = 1;
    brg = _XTAL_FREQ/(4*(baud + 1));
    SPBRG = brg;
    SPBRGH = brg >> 8;
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;
    RCSTAbits.SPEN = 1;
}
void UARTCheck()
{
	
}
void putch(char byte)
{
	while(TXIF == 0);
	TXREG = byte;
}
char getch()
{
	while(RCIF == 0);
	return RCREG;
}
void EEWrite(char addr, char data)
{
    char GIEbit;
    EEADR = addr;
    EEDAT = data;
    EECON1bits.EEPGD = 0;
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
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    return EEDAT;
}
void ADCSetup()
{
    ADCON0bits.ADCS = 0b11; //Ajusta el TAD a FRC
    ADCON1bits.VCFG0 = 0; //Ref-    0=VSS   1=AN2
    ADCON1bits.VCFG1 = 0; //Ref+    0=VDD   1=AN3
    ADCON0bits.ADON = 1;
}
unsigned int ADCRead(char ch)
{
    unsigned int value;
    ADCON0bits.CHS = ch;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO);
    value = ADRESH;
    value = (value << 8) & 0xFF00;
    value = value | ADRESL;
    value = value >> 6;
    return value;
}
void TMR0Setup(char cs, char pre)
{
    OPTION_REGbits.T0CS = cs;
    if(pre < 8)
    {    
        OPTION_REGbits.PSA = 0;
        OPTION_REGbits.PS = pre;
    }
}
void TMR0Setval(char value)
{
    INTCONbits.T0IF = 0;
    TMR0 = value; //256 - (n / PRE) * (_XTAL_FREQ / 4)
}
char TMR0Getval()
{
    return TMR0;
}
void TMR1Setup(char cs, char pre)
{
    T1CONbits.TMR1CS = cs;
    T1CONbits.T1CKPS = pre;
}
void TMR1Setval(unsigned int value)
{
    T1CONbits.TMR1ON = 0;    
    TMR1L = value; //65536 - (n / PRE) * (_XTAL_FREQ / 4)
    TMR1H = (char) value >> 8;
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 1;
}
unsigned int TMR1Getval()
{
    unsigned int value;
    value = TMR1H;
    value = value << 8;
    value |= TMR1L; 
    return value;
}
void TMR2Setup(char pre, char post)
{
    T2CONbits.T2CKPS = pre; //00=1:1, 01=1:4 1x=1:16
    T2CONbits.TOUTPS = post; //0000=1:1 .. 1111=1:16
}
void TMR2Setval(char value)
{
    T2CONbits.TMR2ON = 0;
    PR2 = value; //(_XTAL_FREQ * n) / (4 * PRE * POST)
    TMR2 = 0;
    PIR1bits.TMR2IF = 0;
    T2CONbits.TMR2ON = 1;
}
char TMR2Getval()
{
	return TMR2;
}
void CCP1Setup(char mode) //RC2
{
    CCP1CONbits.CCP1M = mode;
}
void CCP2Setup(char mode) //RC1
{
    CCP2CONbits.CCP2M = mode;
}
void PWMSetperiod(char period, char pre)
{
    PIR1bits.TMR2IF = 0;
    PR2 = period; //((_XTAL_FREQ * T) / (4 * T2PRE)) - 1  
    T2CONbits.T2CKPS = pre; //00=1:1 01=1:4 1x=1:16
    T2CONbits.TMR2ON = 1; //Activa el Timer2
}
void PWM1Setduty(unsigned short mod) //10bit
{
    TRISCbits.TRISC2 = 1;
    CCPR1L = mod >> 2;//Actualiza el valor del ciclo pwm 8bits significativos
    CCP1CONbits.DC1B = mod & 0x0003; //Actualiza el valor de los 2bits menos sig
    TRISCbits.TRISC2 = 0;
}
void PWM2Setduty(unsigned short mod) //10bit
{
    TRISCbits.TRISC1 = 1;
    CCPR2L = mod >> 2;//Actualiza el valor del ciclo pwm 8bits significativos
    CCP2CONbits.DC2B0 = mod & 1; //Actualiza el valor de los 2bits menos sig
    CCP2CONbits.DC2B1 = (mod >> 1) & 1;
    TRISCbits.TRISC1 = 0;
}
