
// PIC18F8720 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#define _XTAL_FREQ 4000000
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <plib.h>
//#include <pic18.h>
//#include "i2c_soft_lib.h"
#include "bsp.h"
#include "config.h"
#include "i2c_soft_library.h"

/*
 *
 */
void main() {

    ADCON1=0x0F;
    TRISA=1;
    TRISC=0;
 //   CONFIG3L=0x80;// xq no anda???? //1 = Wait selections unavailable, device will not wait // 00 = Extended Microcontroller mode

    // ANS
    while(1)
    {

        led_on(LED2);
        __delay_ms(100);
        led_off(LED2);
        __delay_ms(100);

//        int i=0;
//       if (0!=PORTAbits.RA5){
//            int i=0;
//            for( i=0;i<4;i++){
//                led_on(i);
//                __delay_ms(100);
//                led_off(i);
//                __delay_ms(100);
//            }
//        }else{
//
//           for(i=4;i<8;i++){
//
//                 led_on(i);
//                __delay_ms(100);
//                led_off(i);
//                __delay_ms(100);
//           }
//       }

    }
}

