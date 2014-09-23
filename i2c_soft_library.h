#ifndef __i2c_h__
#define __i2c_h__


#include <stdint.h>
#define uchar unsigned char

void start(void);
void stop(void);
uint8_t clock(void);
uint8_t write(uchar byte);
uchar read(uint8_t acknowledgment);
uint8_t EEPROM_byte_write(uchar address, uchar byte);
uint8_t EEPROM_sequential_read(uchar *block, uchar address,uchar size);
uint8_t EEPROM_acknowledge_polling(void);
void EEPROM_busy(void);
void initialization(void);
#endif