#ifndef MAZESOLVING_H
#define MAZESOLVING_H

#include <reg51.h>
#include <stdio.h>
#include "delay.h"
#include "UART.h"
#include "servo.h"
#include "BYJ48.h"
#include "HCSR04.h"

void inicio(void);
void maze_solving(void);
void go_forward(void);
void go_left(void);
void go_right(void);
void turn_180(void);

#endif