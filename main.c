/*Este programa sirve para probar las entradas y salidas de la placa. prende la mitad alta o baja del array de leds en funcion de una entrada*/
#include <xc.h>
#define _XTAL_FREQ 4000000
#include "bsp.h"
#include "config.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <plib.h>
//#include <pic18.h>
#include "i2c_soft_library.h"

void main() {
    config();
    while(1)
    {
       int i=0;
       if (0!= INPUT8){
            int i=0;

            for( i=0;i<=3;i++){
                led_on(i);
                __delay_ms(100);
                led_off(i);
                __delay_ms(100);
            }
        }else{
           for(i=4;i<=7;i++){

                led_on(i);
                __delay_ms(100);
                led_off(i);
                __delay_ms(100);
           }
       }
    }
}

