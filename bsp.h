
#ifndef __bsp_h__
#define __bsp_h__

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define led0 PORTCbits.RC1
#define led1 PORTCbits.RC0
#define led2 PORTCbits.RC6
#define led3 PORTCbits.RC7
#define led4 PORTCbits.RC2
#define led5 PORTCbits.RC3
#define led6 PORTCbits.RC4
#define led7 PORTCbits.RC5

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7

void led_on(int numeroLed);
void led_off(int numeroLed);

#endif