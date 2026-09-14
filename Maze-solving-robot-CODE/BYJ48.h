// BYJ48.h
#ifndef BYJ48_H
#define BYJ48_H

#include <reg51.h>

void stepper_init(void);
void stepper_forward(unsigned int steps);
void stepper_turn_180(void);
void stepper_go_left(void);
void stepper_go_right(void);
unsigned int delay_acel(unsigned int total_steps, unsigned int i_steps);

#endif