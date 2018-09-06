/* 
 * File:LCD.MIO
 * Author: Civadda Matias
 * Comments:QSYO 
 * Revision history: 3/6/2018
 */
#include <xc.h> // include processor files - each processor file is guarded.
/*Defines************************************************************************/
#define RS			PORTEbits.RE2
#define RW			PORTEbits.RE1
#define	E			PORTEbits.RE0

#define DelayLCD 5
#define TimeLCD 4

/*Funciones *******************************************************************/
void LCD_Inicio(void);
void datos(unsigned char);
void LCD_Mensaje(const char *);
void Crear_Caracter(char[]);
void instrucciones8bits(unsigned char);
void LCD_Tic(void);

/*Enums************************************************************************/
enum IncioLCD {
    OFF, MODO_FUNCIONAMIENTO, CLEAR, CURSOR_HOME, MODO_TRANFERENCIA, ON, WRITE, END
} LCD_Init;

