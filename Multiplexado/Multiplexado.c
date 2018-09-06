#include "Multiplexado.h"

/* Funcion Principal
 * Divide en unidades cada display
 */
void Multiplexado(int Dato) {

    switch (Multiplex) {
        case MILES:
            DISP4 = 0;
            if (Dato > 1000) {
                Mask(Dato / 1000);
                DISP1 = 1;
                DOT = 1;
            }
            break;
            /******************************************************************/
        case CENTENAS:
            DOT = 0;
            DISP1 = 0;
            if (Dato > 100) {
                Mask((Dato % 1000) / 100);
                DISP2 = 1;
            }
            break;
            /******************************************************************/
        case DECENAS:
            DISP2 = 0;
            if (Dato > 10) {
                Mask(((Dato % 1000) % 100) / 10);
                DISP3 = 1;
            }
            break;
            /******************************************************************/
        case UNIDADES:
            DISP3 = 0;
            Mask(((Dato % 1000) % 100) % 10);
            DISP4 = 1;
            break;
            /******************************************************************/
        default:
            Multiplex = MILES;
    }
}

/* Funcion de enmascarado
 */
void Mask(char Dato) {
    LATA = (LATA & 0xF0) | (Dato & 0x0F);
}

/* Funcion para timer 
 * necesaria para medir tiempos
 */
void tic_Multiplexado(void) {
    Multiplex++;
}