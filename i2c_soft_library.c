#include <xc.h>
#define _XTAL_FREQ 4000000
#include <stdio.h>
#include "i2c_soft_library.h"


#define uchar unsigned char
#define SDA PORTJbits.RJ5 /* microcontroller's I/O lines */
#define SCL PORTJbits.RJ6 /* assigned to I2C lines */



/****************************************************
Issuing of START condition.
****************************************************/
void start(void){
    TRISJ=0x00; // PORTJ OUTPUT
    SDA = SCL = 1;
    SDA = 0;
     __delay_us(5);  /* it places NOP instruction */
                     /* into executable code */
    SCL = 0;
}
/****************************************************
Issuing of STOP condition.
****************************************************/
void stop(void){
    TRISJ=0x00; //PUERTO J OUTPUT
    SDA = 0;
    SCL = 1;
    int a=5;
     __delay_ms(5);
    SDA = 1;
}
/****************************************************
Clock pulse generation. The function returns data
or acknowledgment bit.
****************************************************/
uint8_t clock(void){
    uint8_t level; /* state of SDA line */
    TRISJ=0x20;//SCL o RJ6 = OUTPUT, SDA o RJ5= INPUT
    SCL = 1;
     __delay_ms(1);  /* it places NOP instruction into executable code */
    while(!SCL); /* if a pulse was stretched */
     __delay_ms(3);  /* it places NOP instruction  :into executable code */
    level = SDA;
     __delay_us(2);  /* it places NOP instruction  into executable code */

    SCL = 0;
    return(level);
}
/****************************************************
Writing a byte to a slave, with most significant
bit first. The function returns acknowledgment bit.
****************************************************/
uint8_t write(uchar byte){
    uchar mask = 0x80;
    TRISJ=0x00;
    while(mask){
        if (byte & mask)
        SDA = 1;
        else
        SDA = 0;
        clock();
        mask >>= 1; /* next bit to send */
    }
    SDA = 1; /* releasing of the line */
    return(clock()); /* a slave should acknowledge */
}
/****************************************************
Reading byte from a slave, with most significant
bit first. The parameter indicates, whether to
acknowledge (1) or not (0).
****************************************************/
uchar read(uint8_t acknowledgment){
    TRISJ=0x60;
    uchar mask = 0x80,
    byte = 0x00;
    while(mask){
        if (clock())
        byte |= mask;
        mask >>= 1; /* next bit to receive */
    }
    if (acknowledgment){
        TRISJ=0x00;
        SDA = 0;
        clock();
        TRISJ=0x00;
        SDA = 1;
    }else{
        SDA = 1;
        clock();
    }
    return(byte);
}

#define EEPROM 0xAE       /* slave address, data direction bit = 0 */
uint8_t EEPROM_byte_write(uchar address, uchar byte){ //direccion de slave y byte a escribir

    uint8_t status;
    status = 0;             /* failure by default */
    start();
    if (!write(EEPROM))     /* write operation    */
    if (!write(address))  /* byte address       */
    if (!write(byte))
        status = 1;       /* success            */
    stop();
    return(status);
}

#define NO_ACK 0
#define ACK    1

uint8_t EEPROM_sequential_read(uchar *block, uchar address,uchar size){//direccion inicial, direccion slave, tamano dato a leer
    uint8_t status;
    status = 0;                    /* failure by default */
    start();
    if (!write(EEPROM))            /* write operation...  load the EEPROM?s internal address counter with the initial value    */
    if (!write(address)){         /* initial address    */
        start();
        if (!write(EEPROM | 0x01)){ /* read operation     */
            TRISJ = 0x60;
            while(size--)
                *block++ = read(size ? ACK : NO_ACK); // tomas no entiendo esta linea
            status = 1;              /* success            */
    }
}
stop();
return(status);
}

uint8_t EEPROM_acknowledge_polling(void){
    uint8_t status;
    start();
    status = write(EEPROM);
    stop();
    return(status);   /* if 1, the write cycle is in progress */
}

void EEPROM_busy(void){
    while(EEPROM_acknowledge_polling())
    __delay_ms (1);   /* about 1 msec */
}

/***************************************/
#define T1_SETP_ADDR 0 /* starting locations of set point */
#define T2_SETP_ADDR 4 /* values of temperatures */

/****************************************************
Global variables.
****************************************************/
float t1_setp, /* temperaturesí set points */
t2_setp;

/****************************************************
Initialization of the system.
****************************************************/
void initialization(void){
    EEPROM_sequential_read(&t1_setp,T1_SETP_ADDR,4);
    EEPROM_sequential_read(&t2_setp,T2_SETP_ADDR,4);
}