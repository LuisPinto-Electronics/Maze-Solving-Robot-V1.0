#ifndef UART_H
#define UART_H

#include <reg51.h>

sfr T2CON  = 0xC8;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2    = 0xCC;
sfr TH2    = 0xCD;

void uart_init(void);
void send_data(char *caracter); 

#endif