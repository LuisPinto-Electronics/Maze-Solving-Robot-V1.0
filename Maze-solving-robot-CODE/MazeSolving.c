
/*
 * MazeSolving.c
 *
 * Description:
 * Implements the left-hand wall-following algorithm used
 * by the maze-solving robot.
 *
 * The robot scans three directions:
 *      Left
 *      Front
 *      Right
 *
 * and selects the first available path according to the
 * following priority:
 *
 *      Left
 *      Front
 *      Right
 *      Turn around
 *
 */
 
#include "MazeSolving.h"

#define RIGHT_ANGLE 15
#define FRONT_ANGLE 95
#define LEFT_ANGLE 170

int distance_left = 0;
int distance_front = 0;
int distance_right = 0;

unsigned char code MIN_distance = 15;

sbit led_1 = P2^4;
sbit led_2 = P2^5;

char buffer[32] = "valor";

void inicio(void)
{
	int i = 0;
	
	led_1 = 0;
	led_2 = 0;
	
  send_data("Maze-Solving Robot\n");
	send_data("STLP Electronica\n");
	
	set_angle(pin_1_0, LEFT_ANGLE);
	send_data("LEFT\n");
	delay_ms(500);
	led_1 = 1;
	led_2 = 1;
	set_angle(pin_1_0, RIGHT_ANGLE);
	send_data("RIGHT\n");
	delay_ms(500);
	led_1 = 0;
	led_2 = 0;
	set_angle(pin_1_0, FRONT_ANGLE);
	send_data("FRONT\n");
	delay_ms(500);
	
	led_1 = 1;
	led_2 = 0;
	
	for(i = 0; i < 20; i ++){
		led_1 = !led_1;
		led_2 = !led_2;
		delay_ms(100);
	}
	
	led_1 = 0;
	led_2 = 0;

}

/*
 * Main maze-solving algorithm.
 *
 * The robot scans the left, front and right directions
 * using the ultrasonic sensor.
 *
 * Priority:
 * 1. Left
 * 2. Front
 * 3. Right
 * 4. Turn around (180°)
 */

void maze_solving(void)
{
	led_2 = 1;
	set_angle(pin_1_0, LEFT_ANGLE); /// rotate the ultrasonic sensor to the left
	delay_ms(100);
	distance_left = get_distance_cm();
	sprintf(buffer, "Distance LEFT: %d cm\n", distance_left);
	send_data(buffer);
	led_1 = !led_1;
	led_2 = !led_2;
	delay_ms(500);
	
	set_angle(pin_1_0, FRONT_ANGLE); /// rotate the ultrasonic sensor to the front
	delay_ms(100);
	distance_front = get_distance_cm();
	sprintf(buffer, "Distance FRONT: %d cm\n", distance_front);
	send_data(buffer);
	led_1 = !led_1;
	led_2 = !led_2;
	delay_ms(500);
	
	set_angle(pin_1_0, RIGHT_ANGLE); /// rotate the ultrasonic sensor to the right
	delay_ms(100);
	distance_right = get_distance_cm();
	sprintf(buffer, "Distance RIGHT: %d cm\n", distance_right);
	send_data(buffer);
	led_1 = !led_1;
	led_2 = !led_2;
	delay_ms(500);
	
	set_angle(pin_1_0, FRONT_ANGLE); /// rotate the ultrasonic sensor to the front
	led_1 = !led_1;
	led_2 = !led_2;
	delay_ms(500);
	led_2 = 0;
	
	if(distance_left >= MIN_distance){ /// Left path is free
		send_data("Left\n\n");
		go_left(); /// turn to the left
		send_data("Go Forward\n");
		go_forward(); /// go ahead
		return; /// exit the function after executing the selected movement
	}
	else{ /// Left path is blocked
		
		if(distance_front >= MIN_distance){ ///Front path is free
			send_data("Go Forward\n\n");
			go_forward();
			return; /// exit the function after executing the selected movement
		}
		else{ /// front path is blocked

			if(distance_right >= MIN_distance){ /// right path is free
				send_data("Right\n\n");
				go_right();
				send_data("Go Forward\n");
				go_forward();
				return; /// exit the function after executing the selected movement
			}
			else{ // No path is available, turn around
				send_data("180 degrees\n\n");
				turn_180();
				send_data("Go Forward\n");
				go_forward();
				return; /// exit the function after executing the selected movement
			}
		}
		
	}/// end else
}

void go_forward(void)
{
	stepper_forward(385); /// moves the robot forward one cell
}

void go_left(void)
{
	stepper_go_left();
}

void go_right(void)
{
	stepper_go_right();
}

void turn_180(void)
{
	stepper_turn_180();
}