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
Copyright (c) 2016 released beMicro.  All rights reserved.
beMicro autoriza el uso, modificacion,copia y distribucion de este software.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY 
INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS
OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS.
*******************************************************************************/
void KBSetup();
char KBScan(); //Retorna 1 si existe dato 
char KBGetchar(char n); //Recupera valor ASCII
void KBGetstring(char *msg, char len); //Recupera un string
#include "keypad.c"
