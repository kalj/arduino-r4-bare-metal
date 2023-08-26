#include "gpio.h"

#include "pin_config.h"

void setPinMode(unsigned long pin, PinMode mode) {
    configPin(pin, mode<<2);
}  

void setPinValue(unsigned long pin, PinLevel lvl) {
    unsigned long port = pin>>8;
    int pin_bit = pin&0xff;
    if (lvl == PIN_LEVEL_HIGH) {
        PCNTR3(port) = (1<<pin_bit);
    } else {
        PCNTR3(port) = (1<<(pin_bit+16));
    }        
}
