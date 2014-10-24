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
    all_led_off();
    while(1)
    {
        led_on(3);
        start();
        write(0x0A);
        led_off(3);
        stop();
//        write(EEPROM);
//        uint8_t address= 0x00;
//        uint8_t byte = 0x0F;
//        uint8_t result=0;
//        result=EEPROM_byte_write(address, byte);
//        if (0!=result){
//            led_on(1);
//            led_on(2);
//            led_off(4);
//            led_off(5);
//        }else{
//            led_off(1);
//            led_off(2);
//            led_on(4);
//            led_on(5);
//        }
      }
}
/******************************************************************8*/
//       int i=0;
//       if (0!= INPUT8){
//            int i=0;
//
//            for( i=0;i<=3;i++){
//                led_on(i);
//                __delay_ms(100);
//                led_off(i);
//                __delay_ms(100);
//            }
//        }else{
//           for(i=4;i<=7;i++){
//
//                led_on(i);
//                __delay_ms(100);
//                led_off(i);
//                __delay_ms(100);
//           }
//       }
//    }
//}

