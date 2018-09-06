/* 
 * File:   Multiplexado.h
 * Author: Matias Civadda
 *
 * Created on 3 de Septiembre de 2018
 */
#include <xc.h>
#define DISP1   LATAbits.LA4
#define DISP2   LATAbits.LA5
#define DISP3   LATEbits.LATE0
#define DISP4   LATEbits.LATE1
#define DOT     LATEbits.LATE2

/*Enum - Maquina de Estados ***************************************************/

enum Estado_Displays {
    MILES, CENTENAS, DECENAS, UNIDADES
} Multiplex = MILES;

/*Funciones *******************************************************************/
void Multiplexado(int);         //Funcion Principal en el loop
void Mask(char);                //enmascarado 
void tic_Multiplexado(void);    //Funcion para timer 