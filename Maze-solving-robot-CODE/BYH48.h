#ifndef BYJ48_H
#define BYJ48_H

#include <reg51.h>

sbit INT1_izq = P1^4;
sbit INT2_izq = P1^5;
sbit INT3_izq = P1^6;
sbit INT4_izq = P1^7;

sbit INT1_der = P2^0;
sbit INT2_der = P2^1;
sbit INT3_der = P2^2;
sbit INT4_der = P2^3;

typedef enum
{
	stepper_izq,
	stepper_der
	
}stepper_t;

void stepper_init(void);
void pasos_(stepper_t motor, signed short pasos);

#endif