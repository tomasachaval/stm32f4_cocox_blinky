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
 //   uint8_t result[50];
    while(1)
    {
        led_off(0);
       
        start();
        write(0xD0);
        led_on(0);
        stop();
        

//       if( EEPROM_sequential_read(result, 0x00, 0x09))
//           led_on(0);
//        for(i=0;i<=255;i++){
//        led_on(3);
//        led_on(5);
//            start();
//            if(!write(0xa4))
//                led_off(5);
//            led_off(3);
//            stop();
//        }
//        led_on(2);
       // __delay_ms(1); //TOMAS
      
//        write(EEPROM);
//        uint8_t address= 0x00;
//        uint8_t byte = 0x0F0A;
//        uint8_t dato=0;
//        if(EEPROM_byte_write(address, byte))
//            if(EEPROM_sequential_read(&dato, address,2))
//                if(dato=byte)
//                    led_on(5);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);
//            __delay_ms(100);

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

