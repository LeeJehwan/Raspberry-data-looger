#include <bcm2835.h>
#include "pcf8574.h"

/* i2c function */
static void i2c_writeByte(char byte){
    char buf[] = {byte};
    bcm2835_i2c_write(buf,1);
}
static char i2c_readByte(){
    char buf[1];
    bcm2835_i2c_read(buf,1);
    return buf[0];
}
/* make beep */
int control_beep(){
    if(!bcm2835_init()) return 1;
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x20);
    bcm2835_i2c_set_baudrate(10000);
    
    beep_on;
    bcm2835_delay(50);
    beep_off;
    
    bcm2835_i2c_end();
    bcm2835_close();
}
