#include <xc.h>
#define _XTAL_FREQ 4000000
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "i2c_soft_library.h"
#include "bsp.h"

//#define uchar unsigned char // 8bit
#define SDA LATJ5//PORTJbits.RJ5 /* microcontroller's I/O lines */
#define SCL LATJ6//PORTJbits.RJ6 /* assigned to I2C lines */
#define wp 0x80  //haciendo or con este numero hago que trisj7=1---> que es una salida. ya que este sirve para manejar el write protect

/****************************************************
Issuing of START condition.
 ****************************************************/
void start(void) {
    TRISJ = 0x00;
    LATJ7 = 0; // HAGO WP =0 PARA PODER ESCRIBIR// LO HICE POR HARDWARE SACANDO R5 Y PONIIENDO CABLE A MASA
    SDA = SCL = 1;
    SDA = 0;
    __delay_us(5); /* it places NOP instruction */
    /* into executable code */
    SCL = 0;
}

/****************************************************
Issuing of STOP condition.
 ****************************************************/
void stop(void) {
    TRISJ = 0x00;
    LATJ7 = 0; //HAGO WP =0 PARA PODER ESCRIBIR// LO HICE POR HARDWARE SACANDO R5 Y PONIIENDO CABLE A MASA
    SDA = 0;
    SCL = 1;
    __delay_us(5);
    SDA = 1;
}

/****************************************************
Clock pulse generation. The function returns data
or acknowledgment bit.
 ****************************************************/
uint8_t clock(void) {
    uint8_t level; /* state of SDA line */
    TRISJ = 0x32; //SCL o RJ6 = OUTPUT, SDA o RJ5= INPUT
    LATJ7 = 0; //HAGO WP =0 PARA PODER ESCRIBIR// LO HICE POR HARDWARE SACANDO R5 Y PONIIENDO CABLE A MASA
    SCL = 1;
    __delay_us(1); /* it places NOP instruction into executable code */
    while (!SCL); /* if a pulse was stretched */
    __delay_us(3); /* it places NOP instruction  :into executable code */
    level = SDA;
    __delay_us(2); /* it places NOP instruction  into executable code */

    SCL = 0;
    return (level);
}

/****************************************************
Writing a byte to a slave, with most significant
bit first. The function returns acknowledgment bit.
 ****************************************************/
uint8_t write(uint8_t byte) {
    uint8_t mask = 0x80;
   // uint8_t  i=0, p=0;
    TRISJ = 0x00;
    LATJ7 = 0; ////HAGO WP =0 PARA PODER ESCRIBIR// LO HICE POR HARDWARE SACANDO R5 Y PONIIENDO CABLE A MASA
    while (mask) {
        TRISJ = 0x00;
        if (byte & mask){
            SDA = 1;
        }else{
            SDA = 0;
        }
        clock();
        mask = mask >> 1; /* next bit to send */
    }
    SDA = 1; /* releasing of the line */

    return (clock()); /* a slave should acknowdge */
}

/****************************************************
Reading byte from a slave, with most significant
bit first. The parameter indicates, whether to
acknowledge (1) or not (0).
 ****************************************************/
uint8_t read(uint8_t acknowledgment) {
    TRISJ = 0x60;
    uint8_t mask = 0x80,
            byte = 0x00;
    while (mask) {
        if (clock())
            byte |= mask;
        mask >>= 1; /* next bit to receive */
    }
    if (acknowledgment) {
        TRISJ = 0x00;
        SDA = 0;
        clock();
        TRISJ = 0x00;
        SDA = 1;
    } else {
        SDA = 1;
        clock();
    }
    return (byte);
}

/* uso IC06. SU DIR ES 10 // slave address, 1010=control code, b0-->indica el bloque de 512k
dentro de la memoria,A1y A0--> indican que memoria es. r/w-->data direction bit = 0 para hacerle el or. */
uint8_t EEPROM_byte_write(uint8_t address, uint8_t byte) { //direccion dentro de la memoria y byte a escribir
    LATJ7 = 0; // //HAGO WP =0 PARA PODER ESCRIBIR// LO HICE POR HARDWARE SACANDO R5 Y PONIIENDO CABLE A MASA
    uint8_t status=0; /* failure by default */
//    status = 0;
    start();
    if (!write(EEPROM)) { /* write operation    */
        if (!write(address)) { /* byte address       */
            if (!write(byte)) {
                status = 1; /* success            */
            }
        }
    }
    stop();
    return (status);
}

#define NO_ACK 0
#define ACK    1

uint8_t EEPROM_sequential_read(uint8_t *block, uint8_t address, uint8_t size) {//direccion inicial, direccion slave, tamano dato a leer
    uint8_t status;
    status = 0; /* failure by default */
    start();
    if (!write(EEPROM)) /* write operation...  load the EEPROM?s internal address counter with the initial value    */
        if (!write(address)) { /* initial address    */
            start();
            if (!write(EEPROM | 0x01)) { /* read operation     */
                //TRISJ = 0x60;
                TRISJ = 0x60;
                while (size--)
                    *block++ = read(size ? ACK : NO_ACK); // tomas no entiendo esta linea
                status = 1; /* success            */
            }
        }
    stop();
    return (status);
}

/*The first function determines the ready/busy status of the EEPROM. If you assume that after
 the write sequence a program execution may be suspended until the write cycle is complete, the EEP-
ROM_busy() function can be used.*/
uint8_t EEPROM_acknowledge_polling(void) {
    uint8_t status;
    start();
    status = write(EEPROM);
    stop();
    return (status); /* if 1, the write cycle is in progress */
}

void EEPROM_busy(void) {
    while (EEPROM_acknowledge_polling())
        __delay_ms(1); /* about 1 msec */
}

///***************************************/
//#define T1_SETP_ADDR 0 /* starting locations of set point */
//#define T2_SETP_ADDR 4 /* values of temperatures */
//
///****************************************************
//Global variables.
//****************************************************/
//float t1_setp, /* temperaturesí set points */
//t2_setp;
//
///****************************************************
//Initialization of the system.
//****************************************************/
//void initialization(void){
//    EEPROM_sequential_read(&t1_setp,T1_SETP_ADDR,4);
//    EEPROM_sequential_read(&t2_setp,T2_SETP_ADDR,4);
//}