
/*
 * servo.c
 *
 * Author: Luis J. Pinto G.
 *
 * Description:
 * Software driver for up to four hobby servo motors.
 *
 * The PWM signal is generated using Timer 0 interrupts,
 * allowing independent angle control for each servo.
 *
 * Supported servo outputs:
 *      P1.0
 *      P1.1
 *      P1.2
 *      P1.3
 */
 
#include "servo.h"

volatile unsigned char activar_1 = 0, activar_2 = 0, activar_3 = 0, activar_4 = 0;
volatile unsigned int valor_tiks_1 = 0, valor_tiks_2 = 0, valor_tiks_3 = 0, valor_tiks_4 = 0;
volatile unsigned int tiks = 0;


/*
 * Initializes Timer 0 for software PWM generation.
 *
 * Timer 0 operates in Mode 2 (8-bit auto-reload)
 * and generates the interrupts required to produce
 * the servo control pulses.
 */
void servo_init(void)
{
    TMOD &= 0xF0;
    TMOD |= 0x02;   // Timer0, Modo 2 (8 bits, auto-reload)

    TH0 = 0x9C;     // 256 - 100 = 156 = 0x9C  (recarga automática)
    TL0 = 0x9C;     // carga inicial igual

    IE |= 0x82;
    TR0 = 1;
}


/*
 * Sets the desired angle of the selected servo.
 *
 * Parameters:
 *      pin       Servo output pin.
 *      angle     Desired angle (degrees).
 */
void set_angle(pin_servo_t pin, unsigned char angulo_int)
{
	switch(pin){
		
		case pin_1_0:
			valor_tiks_1 = angulo_tiks(angulo_int);
			activar_1 = 1;
		break;
		
		case pin_1_1:
			valor_tiks_2 = angulo_tiks(angulo_int);
			activar_2 = 1;
		break;
		
		case pin_1_2:
			valor_tiks_3 = angulo_tiks(angulo_int);
			activar_3 = 1;
		break;
		
		case pin_1_3:
			valor_tiks_4 = angulo_tiks(angulo_int);
			activar_4 = 1;
		break;
		
	}
}


/*
 * Timer 0 Interrupt Service Routine.
 *
 * Generates the PWM pulses for all enabled servos.
 * The pulse width depends on the angle previously
 * selected with set_angle().
 */

void ISR_servo(void) interrupt 1
{
	TF0 = 0; /// limpiar la bandera
	
	tiks ++;
	
	/******************************/
	if(activar_1 == 1){
	if(tiks == 1){
		pin_servo_1 = 1;
	}
	else if(tiks == valor_tiks_1){
		pin_servo_1 = 0;
	}
	}
	/******************************/
	if(activar_2 == 1){
	if(tiks == 1){
		pin_servo_2 = 1;
	}
	else if(tiks == valor_tiks_2){
		pin_servo_2 = 0;
	}
	}
	/******************************/
	if(activar_3 == 1){
	if(tiks == 1){
		pin_servo_3 = 1;
	}
	else if(tiks == valor_tiks_3){
		pin_servo_3 = 0;
	}
	}
	/******************************/
	if(activar_4 == 1){
	if(tiks == 1){
		pin_servo_4 = 1;
	}
	else if(tiks == valor_tiks_4){
		pin_servo_4 = 0;
	}
	}	
	/******************************/
	
	if(tiks == PERIODO_TIKS){
		tiks = 0;
	}
}

/*
 * Converts an angle (degrees) into timer ticks.
 *
 * Parameters:
 *      angle   Servo angle (0° to 180°).
 *
 * Returns:
 *      Pulse width expressed in timer ticks.
 */

unsigned int angulo_tiks(unsigned char angulo)
{
	return 4 + (((unsigned int)angulo * 125 + 512) >> 10);
}