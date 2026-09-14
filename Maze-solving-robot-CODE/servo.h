#ifndef SERVO_H
#define SERVO_H

#include <reg51.h>

#define PERIODO_TIKS 200 

/// angulo minimo 15 grados

sfr T2MOD = 0xC9; /// registro especial

sbit pin_servo_1 = P1^0;
sbit pin_servo_2 = P1^1;
sbit pin_servo_3 = P1^2;
sbit pin_servo_4 = P1^3;

typedef enum /// pines 
{
	pin_1_0 = 0,
	pin_1_1,
	pin_1_2,
	pin_1_3
	
}pin_servo_t;

void servo_init(void);
void set_angle(pin_servo_t pin, unsigned char angulo_int);
unsigned int angulo_tiks(unsigned char angulo);

#endif