#include "LCD_MIO.h"
/*variables globales **********************************************************/
unsigned char LCD_timeout = DelayLCD;
int MS = 0;
unsigned char numer = 0;

char Flecha[] = {
    0b10000,
    0b11000,
    0b11100,
    0b11110,
    0b11110,
    0b11100,
    0b11000,
    0b10000,

    0x40
};
char Corazon[] = {
    0x00,
    0x00,
    0x1B,
    0x1F,
    0x1F,
    0x0E,
    0x04,
    0x00,

    0x48
};

void LCD_Inicio(void) {
    while (LCD_Init != END) {
        switch (LCD_Init) {
            case OFF:
                if (LCD_timeout == 0) {
                    LCD_Init = MODO_TRANFERENCIA;
                    LCD_timeout = DelayLCD;
                }
                break;
            case MODO_TRANFERENCIA:
                if (LCD_timeout == 0) {
                    while (LCD_timeout != 0)instrucciones8bits(0x38);
                    LCD_Init = CLEAR;
                    LCD_timeout = DelayLCD;
                }
                break;
            case CLEAR:
                if (LCD_timeout == 0) {
                    while (LCD_timeout != 0)instrucciones8bits(0x01);
                    LCD_Init = CURSOR_HOME;
                    LCD_timeout = DelayLCD;
                }
            case CURSOR_HOME:
                if (LCD_timeout == 0) {
                    while (LCD_timeout != 0)instrucciones8bits(0x02);
                    LCD_Init = MODO_FUNCIONAMIENTO;
                    LCD_timeout = DelayLCD;
                }
                break;
            case MODO_FUNCIONAMIENTO:
                if (LCD_timeout == 0) {
                    while (LCD_timeout != 0)instrucciones8bits(0x06);
                    LCD_Init = ON;
                    LCD_timeout = DelayLCD;
                }
                break;
            case ON:
                if (LCD_timeout == 0) {
                    while (LCD_timeout != 0)instrucciones8bits(0x0C);
                    LCD_Init = WRITE;
                }
                break;
            case WRITE:
                if (LCD_timeout == 0) {
                    while (LCD_timeout != 0)Crear_Caracter(Flecha);
                    while (LCD_timeout != 0)instrucciones8bits(0x02);
                    LCD_Mensaje("Hola");
                    while (LCD_timeout != 0)datos(0x00);
                    LCD_timeout = DelayLCD;
                    LCD_Init = END;
                }
                break;
        }
    }
}

void datos(unsigned char dato) {
    PORTE = 0x00;
    PORTD = dato;
    RS = 1;
    if (LCD_timeout == 3) E = 1;
    if (LCD_timeout == 2) E = 0;
    if (LCD_timeout == 1) RS = 0;
    if (LCD_timeout == 0) LCD_timeout = TimeLCD;
}

void instrucciones8bits(unsigned char instruccion) {
    PORTE = 0x00;
    PORTD = instruccion;
    if (LCD_timeout == 3) E = 1;
    if (LCD_timeout == 2) E = 0;
    if (LCD_timeout == 0) LCD_timeout = TimeLCD;
}

void LCD_Mensaje(const char *caracter) {
    while (*caracter != 0) {
        datos(*caracter);
        caracter++;
    }
}

void Crear_Caracter(char Linea[]) {
    instrucciones8bits(Linea[8]); //linea 8 es la direccion en la CGRAM
    for (int i = 0; i <= 7; i++) {
        datos(Linea[i]);
    }
}

void LCD_Tic(void) {
    if (LCD_timeout) LCD_timeout--;
}
