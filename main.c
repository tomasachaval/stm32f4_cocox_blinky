
// PIC18F8720 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#define _XTAL_FREQ 4000000
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <plib.h>
//#include <pic18.h>
#include "bsp.h"
#include "config.h"
//#include "i2c_soft_library.h"

/*
 *
 */
void main() {

    config();



 //   CONFIG3L=0x80;// xq no anda???? //1 = Wait selections unavailable, device will not wait // 00 = Extended Microcontroller mode

    // ANS
    while(1)
    {


//        led_on(2);
//         __delay_ms(100);
//        led_off(2);
//        __delay_ms(100);

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

