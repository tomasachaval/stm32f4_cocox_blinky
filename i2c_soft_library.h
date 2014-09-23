#ifndef __i2c_h__
#define __i2c_h__


#include <stdint.h>
#define uchar unsigned char

void start(void);
void stop(void);
uint8_t clock(void);
uint8_t write(uint8_t byte);
uchar read(uint8_t acknowledgment);
uint8_t EEPROM_byte_write(uint8_t address, uint8_t byte);
uint8_t EEPROM_sequential_read(uint8_t *block, uint8_t address,uint8_t size);
uint8_t EEPROM_acknowledge_polling(void);
void EEPROM_busy(void);
void initialization(void);
#endif