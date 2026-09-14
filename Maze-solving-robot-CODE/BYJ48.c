/*
 * BYJ48.c
 *
 * Author: Luis J. Pinto G
 *
 * Description:
 * Driver for two 28BYJ-48 stepper motors.
 *
 * This module provides the basic movement functions used
 * by the maze-solving robot:
 *
 *      - Forward
 *      - Backward
 *      - Turn left
 *      - Turn right
 *      - Rotate 180°
 *
 * It also implements a simple acceleration profile to
 * reduce missed steps during motor startup.
 */
 
#include "BYJ48.h"
#include "delay.h"

/// left stepper motor pins
sbit INT1_right = P1^7;
sbit INT2_right = P1^6;
sbit INT3_right = P1^5;
sbit INT4_right = P1^4;

/// right stepper motor pins
sbit INT1_left = P2^3;
sbit INT2_left = P2^2;
sbit INT3_left = P2^1;
sbit INT4_left = P2^0;

/// acceleration profile stored in Flash memory
const unsigned int code aceleracion[5] = {450, 350, 280, 220, 160};

/*
 * Initializes both stepper motors.
 *
 * All motor outputs are disabled to ensure the robot
 * starts in a safe state.
 */

void stepper_init(void)
{
	INT1_left = 0;
	INT2_left = 0;
	INT3_left = 0;
	INT4_left = 0;
	
	INT1_right = 0;
	INT2_right = 0;
	INT3_right = 0;
	INT4_right = 0;
}


/*
 * Moves the robot forward.
 *
 * Parameters:
 *      steps : Number of full steps.
 */
void stepper_forward(unsigned int steps)
{
	int i = 0;
	int speed = 0;
	
	for(i = 0; i < steps; i ++){
		
		speed = delay_acel(steps, i);
		
		INT1_left = 1; /// INT 4
		INT1_right = 1;
		delay_us(speed);
		INT1_left = 0;
		INT1_right = 0;
		
		INT2_left = 1; /// INT 3
		INT2_right = 1;
		delay_us(speed);
		INT2_left = 0;
		INT2_right = 0;
		
		INT3_left = 1; /// INT 2
		INT3_right = 1;
		delay_us(speed);
		INT3_left = 0;
		INT3_right = 0;
		
		INT4_left = 1; /// INT 1
		INT4_right = 1;
		delay_us(speed);
		INT4_left = 0;
		INT4_right = 0;
	}
	
	stepper_init();
	
}

/*
 * Rotates the robot 180 degrees.
 */
void stepper_turn_180(void)
{
	const int steps = 400;
	int speed = 0;
	int i = 0;
	
	for(i = 0; i < steps; i ++){
		
		speed = delay_acel(steps, i);
		
		INT1_left = 1;
		INT4_right = 1;
		delay_us(speed);
		INT1_left = 0;
		INT4_right = 0;
		
		INT2_left = 1;
		INT3_right = 1;
		delay_us(speed);
		INT2_left = 0;
		INT3_right = 0;
		
		INT3_left = 1;
		INT2_right = 1;
		delay_us(speed);
		INT3_left = 0;
		INT2_right = 0;
		
		INT4_left = 1;
		INT1_right = 1;
		delay_us(speed);
		INT4_left = 0;
		INT1_right = 0;
	
	}
	
	stepper_init();
}

/*
 * Rotates the robot 90 degrees to the right
 */

void stepper_go_right(void)
{
	int steps = 400;
	int speed = 0;
	int i = 0;
	
	for(i = 0; i < steps; i ++){
		
		speed = delay_acel(steps, i);
		
		INT1_left = 1;
		//INT4_right = 1;
		delay_us(speed);
		INT1_left = 0;
		//INT4_right = 0;
		
		INT2_left = 1;
		//INT3_right = 1;
		delay_us(speed);
		INT2_left = 0;
		//INT3_right = 0;
		
		INT3_left = 1;
		//INT2_right = 1;
		delay_us(speed);
		INT3_left = 0;
		//INT2_right = 0;
		
		INT4_left = 1;
		//INT1_right = 1;
		delay_us(speed);
		INT4_left = 0;
		//INT1_right = 0;
	
	}
	
	stepper_init();
}

/*
 * Rotates the robot 90 degrees to the left.
 */

void stepper_go_left(void)
{
	int speed = 0;
	int steps = 400;
	int i = 0;
	
	for(i = 0; i < steps; i ++){
		
		speed = delay_acel(steps, i);
		
		//INT4_left = 1;
		INT1_right = 1;
		delay_us(speed);
		//INT4_left = 0;
		INT1_right = 0;
		
		//INT3_left = 1;
		INT2_right = 1;
		delay_us(speed);
		//INT3_left = 0;
		INT2_right = 0;
		
		//INT2_left = 1;
		INT3_right = 1;
		delay_us(speed);
		//INT2_left = 0;
		INT3_right = 0;
		
		//INT1_left = 1;
		INT4_right = 1;
		delay_us(speed);
		//INT1_left = 0;
		INT4_right = 0;
	
	}
	
	stepper_init();
}

/*
 * Calculates the motor delay according to
 * the current position in the movement.
 *
 * A simple five-stage acceleration profile is
 * applied during the first 10% of the movement.
 *
 * Parameters:
 *      total_steps : Total movement steps.
 *      i_steps     : Current step.
 *
 * Returns:
 *      Delay in microseconds.
 */

unsigned int delay_acel(unsigned int total_steps, unsigned int i_steps)
{
    unsigned int accel_steps = total_steps / 10;   /// Solo acelerar el 10% de los pasos

    if(accel_steps < 5)
        accel_steps = 5; 

    if(i_steps < (accel_steps * 1) / 5)
        return aceleracion[0];

    else if(i_steps < (accel_steps * 2) / 5)
        return aceleracion[1];

    else if(i_steps < (accel_steps * 3) / 5)
        return aceleracion[2];

    else if(i_steps < (accel_steps * 4) / 5)
        return aceleracion[3];

    else
        return aceleracion[4];
}