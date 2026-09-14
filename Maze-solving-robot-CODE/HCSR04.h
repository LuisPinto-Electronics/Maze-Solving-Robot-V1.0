#ifndef HCSR04_H
#define HCSR04_H

#include <reg51.h>

void sensor_HCSR04_init(void);
unsigned int get_distance_cm(void);

#endif