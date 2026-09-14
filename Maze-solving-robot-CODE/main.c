
/*
 * Maze-Solving Robot Firmware
 *
 * Copyright (c) 2026 Luis J. Pinto G.
 *
 * Licensed under the Apache License 2.0.
 * See the LICENSE file in the project root for license information.
 */
/*
	
	This is a simple program that controls the robot. The algorithm does not remember the route, 
	it can only find an exit located on the perimeter of the maze, it cannot find the exit 
	inside the maze, that's why you must design a maze which contains the exit around it, or in a corner.
	You can change the values or limits according to your robot (in case you have designed your own).
	
	Requirements:
	
	According to my design, you must connect a battery that provides the robot with a voltage between 6.8 V and 8 V.
	If you put less voltage, the robot will not work correctly or even it will not work.
	If you want to upload your own firmware, make sure to disconnect the jumper which supplies voltage to the microcontroller. 
	I recommend following these steps.
	
	1. Open the project's output folder, it contains the .hex file.
	2. Select the STC89C52RC microcontroller.
	3. Disconnect the microcontroller power jumper and press the RESET button.
	4. Click the "Download/Program" button.
	5. Connect the power supply jumper again and realase the RESET button very quickly, and wait until the firmware has been uploaded successfully.
	
*/

#include <reg51.h>
#include "delay.h"
#include "UART.h"
#include "servo.h"
#include "HCSR04.h"
#include "BYJ48.h"
#include "MazeSolving.h"

sbit led_1 = P2^4;
sbit led_2 = P2^5;

/*
	Timer 0 -> Servomotor
	Timer 1 -> HCSR04
	Timer 2 -> UART BaudRate Generator
*/


int main(void)
{
	
	/// initialize libraries
	stepper_init();
	uart_init();
	servo_init();
	sensor_HCSR04_init();
	
	inicio();
	
	while(1)
	{
		maze_solving(); /// this function contains the complete maze-solving algorithm.
	}
}