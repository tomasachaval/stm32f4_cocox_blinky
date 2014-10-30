#ifndef __i2c_h__
#define __i2c_h__

#define EEPROM 0XA4 /*A6=0b10100110       uso IC06. SU DIR ES 10 // slave address, 1010=control code, b0-->indica el bloque de 512k
dentro de la memoria,A1y A0--> indican que memoria es. r/w-->data direction bit = 0 para hacerle el or. */
#define RTC 1101000// a esta direccion le tengo que agregar el ultimo bit que es 1 para leer y queda D0
#include <stdint.h>
//#define uchar unsigned char

void start(void);
void stop(void);
uint8_t clock(void);
uint8_t write(uint8_t byte);
uint8_t read(uint8_t acknowledgment);
uint8_t EEPROM_byte_write(uint8_t address, uint8_t byte); /* address boundaries 0000h to FFFFh and 10000h to 1FFFFh*/
uint8_t EEPROM_sequential_read(uint8_t *block, uint8_t address,uint8_t size); /* address boundaries 0000h to FFFFh and 10000h to 1FFFFh*/
uint8_t EEPROM_acknowledge_polling(void);
void EEPROM_busy(void);
void initialization(void);
#endif