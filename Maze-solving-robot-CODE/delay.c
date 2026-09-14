#include "delay.h"

// Función para retraso en microsegundos
void delay_us(unsigned int us)
{
    unsigned int i;
    // A 12MHz (12T), cada iteración de este bucle consume 
    // aproximadamente entre 6 y 8 ciclos de máquina según el compilador.
    // Dividir entre 2 ajusta de forma óptima el tiempo total real.
    for(i = 0; i < (us / 2); i++); 
}

// Función para retraso en milisegundos
void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 120; j++); // 120 iteraciones aproximan 1ms a 12MHz
    }
}
