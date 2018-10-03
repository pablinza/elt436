 /*********************************************************
 *  Libreria Basica para control de teclado matrix
 *  Autor: Pablo Zarate email:pablo@digital-bo.com
 *  Material de uso para aprendizaje en ELT436 U.E.B.
 *  (nota) Las filas B7-B4 deben ser entradas pullups
 *  Se debe definir los siguientes literales
 *  #define KB_PORT Port de salida
 *	#define KB_TRIS Tris de Port
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
void KBSetup();
char KBScan(); //Retorna 1 si existe dato 
char KBGetval(char n); //Recupera valor Decimal
char KBGetchar(char n); //Recupera valor ASCII
void KBGetstring(char *msg, char len); //Recupera un string
#include "keypad.c"
