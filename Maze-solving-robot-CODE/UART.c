#include <reg51.h>
#include "UART.h"

void uart_init(void)
{
    /*
       Timer2 como generador de baud rate (RCLK=1, TCLK=1).

       Formula (Modo baud rate generator, clock fijo = Fosc/2
           baud = Fosc / (32 * (65536 - [RCAP2H,RCAP2L]))

       Para 4800 baudios a 12MHz:
           65536 - 12000000/(32*4800) = 65536 - 78.125 =~ 65458 = 0xFFB2
           (baud real resultante ~4807.7, error ~0.16%, aceptable)
    */
    T2CON = 0x34;   // TF2 EXF2 RCLK TCLK EXEN2 TR2 C/T2 CP/RL2 = 00110100

    RCAP2H = 0xFF;
    RCAP2L = 0xB2;
    TH2 = 0xFF;     // carga inicial igual al valor de recarga
    TL2 = 0xB2;

    SCON = 0x50;    // Modo 1 (8 bits), REN=1 (habilita recepcion)

    /// No actives ES si vas a esperar TI por polling en send_char.
}

void send_data(char *caracter)
{
    int i = 0;
    while(caracter[i] != '\0')
    {
        SBUF = caracter[i];
        while(TI == 0);
        TI = 0;
        i++;
    }
}