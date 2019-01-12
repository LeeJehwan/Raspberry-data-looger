#ifndef __PCF8574_H__
#define __PCF8574_H__


#define beep_on i2c_writeByte(0x7F & i2c_readByte())
#define beep_off i2c_writeByte(0x80 | i2c_readByte())

/* i2c function  */
static void i2c_writeByte(char byte);
static char i2c_readByte();

int control_beep();


#endif
