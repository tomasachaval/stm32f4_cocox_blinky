
#ifndef __bsp_h__
#define __bsp_h__

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define led0 LATC1
#define led1 LATC0
#define led2 LATC6
#define led3 LATC7
#define led4 LATC2
#define led5 LATC3
#define led6 LATC4
#define led7 LATC5
/*ENTRADAS DEL SLOT DE LA IZQ*/
#define INPUT0 PORTHbits.RH5
#define INPUT1 PORTHbits.RH6
#define INPUT2 PORTHbits.RH7
#define INPUT3 PORTFbits.RF2
#define INPUT4 PORTFbits.RF3
#define INPUT5 PORTFbits.RF4
#define INPUT6 PORTFbits.RF5
#define INPUT7 PORTAbits.RA6

/*ENTRADAS DEL SLOT DEL MEDIO*/
#define INPUT8  PORTAbits.RA5
#define INPUT9  PORTAbits.RA0
#define INPUT10 PORTAbits.RA1
#define INPUT11 PORTAbits.RA2
#define INPUT12 PORTAbits.RA3
#define INPUT13 PORTFbits.RF0
#define INPUT14 PORTFbits.RF1
#define INPUT15 PORTHbits.RH4










void config (void);
void led_on(int numeroLed);
void led_off(int numeroLed);

#endif