#pragma config FOSC = INTRC_NOCLKOUT, WDTE = OFF, LVP = OFF
#include <xc.h>
#define _XTAL_FREQ 4000000
void interrupt isr()
{
    
    if(INTCONbits.INTF == 1)
    {
        while(PORTBbits.RB0 == 1)
        {
            PORTC = 0;
            PORTD = 0;
            __delay_ms(300);
            PORTCbits.RC1 = 1;
            PORTDbits.RD1 = 1;
            __delay_ms(300);
        }
        INTCONbits.INTF = 0;
    }
    
}
void main()
{
    ANSEL = 0;
    ANSELH = 0;
    TRISC = 0;
    TRISD = 0;
    PORTC = 0;
    PORTD = 0;
    TRISBbits.TRISB0 = 1;
    OPTION_REGbits.INTEDG = 1; //activa detec ascendente
    INTCONbits.INTE = 1; //Habilita interrup externa
    INTCONbits.GIE = 1; //Habilitador global
    while(1)
    {
        PORTCbits.RC0 = 0;
        PORTCbits.RC1 = 0;
        PORTCbits.RC2 = 1;
        //PORTC = 0b00000100;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
        PORTDbits.RD2 = 0;
        //PORTD = 0b00000001;
        __delay_ms(3000);
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;
        __delay_ms(1000);
        PORTCbits.RC0 = 1;
        PORTCbits.RC2 = 0;
        PORTDbits.RD1 = 0;
        PORTDbits.RD2 = 1;
        __delay_ms(3000);
        PORTCbits.RC0 = 0;
        PORTCbits.RC1 = 1;
        __delay_ms(1000);
    }
    
}
