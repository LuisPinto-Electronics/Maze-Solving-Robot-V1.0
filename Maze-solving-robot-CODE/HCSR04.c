/*
 * HCSR04.c
 *
 * Author: Luis J. Pinto G.
 *
 * Description:
 * Driver for the HC-SR04 ultrasonic distance sensor.
 *
 * Timer 1 is configured in Gate mode, allowing the
 * microcontroller to measure the width of the ECHO pulse.
 *
 * The measured pulse width is converted into distance
 * expressed in centimeters.
 */

#include "HCSR04.h"
#include "delay.h"

sbit TRIG_PIN = P3^4;
sbit ECHO_PIN = P3^3;

void sensor_HCSR04_init(void)
{
    // Timer1: GATE=1, C/T=0, Modo 1 (16 bits) -> 1001 = 0x9
    TMOD &= ~0xF0;
    TMOD |= 0x90;
    TH1 = 0;
    TL1 = 0;
    TR1 = 1;
}

unsigned int get_distance_cm(void)
{
    unsigned int tiempo_us;
    TH1 = 0;
    TL1 = 0;
    TRIG_PIN = 1;
    delay_us(10);
    TRIG_PIN = 0;
    while (ECHO_PIN == 0); /// esperita a que se ponga en 1
    while (ECHO_PIN == 1); /// bloquear programa hasta que se ponga en 0 el echo y leer el resultado
    tiempo_us = (TH1 << 8) | TL1; /// combinar 2 bytes para tener el resultado
    return tiempo_us / 58;
}