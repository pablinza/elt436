 /*********************************************************
 *  Libreria Basica para control de teclado matrix
 *  Autor: Pablo Zarate email:pablo@digital-bo.com
 *  Material de uso para aprendizaje en ELT436 U.E.B.
 *  (nota) Las filas B7-B4 deben ser entradas pullups
 *  Se debe definir los siguientes literales
 *  #define KBPORT Port de salida
 *	#define KBTRIS Tris de Port
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
void KBSetup()
{
	KB_TRIS = 0xF0;
	KB_PORT = 0x00;
}
char KBScan()
{
	char i = 4, val;
	char row, col = 0b11110111; //Inicia Columna 1
	while(i--)
	{
		KB_PORT = col;
		NOP();
		if((KB_PORT & 0xF0) != 0xF0)
		{
			row = (KB_PORT) & 0xF0; //Complemento
			col = (col) & 0x0F;
			while((KB_PORT & 0xF0) != 0xF0);
			KB_PORT = 0x00;
            return (row|col); //Retorna R1R2R3R4C1C2C3C4
		}
		col = col >> 1;		
	}
    KB_PORT = 0x00;
	return 0;
}
char KBGetchar(char n)
{
	switch(n)
	{
		case 0b11101110: return 'D';
		case 0b11101101: return '#';
		case 0b11101011: return '0';
		case 0b11100111: return '*';
		case 0b11011110: return 'C';
		case 0b11011101: return '9';
		case 0b11011011: return '8';
		case 0b11010111: return '7';
		case 0b10111110: return 'B';
		case 0b10111101: return '6';
		case 0b10111011: return '5';
		case 0b10110111: return '4';
		case 0b01111110: return 'A';
		case 0b01111101: return '3';
		case 0b01111011: return '2';
		case 0b01110111: return '1';
		default: return '?';
	}
}

char KBGetval(char n)
{
	switch(n)
	{
		case 0b11101110: return 13; //Return
		case 0b11101101: return 15;
		case 0b11101011: return 0;
		case 0b11100111: return 14;
		case 0b11011110: return 12;
		case 0b11011101: return 9;
		case 0b11011011: return 8;
		case 0b11010111: return 7;
		case 0b10111110: return 11;
		case 0b10111101: return 6;
		case 0b10111011: return 5;
		case 0b10110111: return 4;
		case 0b01111110: return 10; //Line Feed
		case 0b01111101: return 3;
		case 0b01111011: return 2;
		case 0b01110111: return 1;
		default: return '?';
	}
}
void KBGetstring(char *msg, char len)
{
	char key;
	while( len --)
	{
		do
		{
			key = KBScan();
		} while(key == 0);
		*msg = KBGetchar(key);
		msg ++;
        delayms(100);
	} 
	*msg = 0;
}
