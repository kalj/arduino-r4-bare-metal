#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include "ra4m1.h"

static inline void enableWritingPmnPFS() {
    // store 0 to PWPR, enabling writing to PFSWE
    PWPR = 0;
    // store 0x40 to PWPR, enabling writing to PmnPFS
    PWPR = 0x40;
}  

static inline void disableWritingPmnPFS() {
    // reset PWPR
    // store 0 to PWPR, enabling writing to PFSWE
    PWPR = 0;
    // store 0x80 to PWPR, disabling writing to PmnPFS
    PWPR = 0x80;
}

static inline void configPin(unsigned long pin, unsigned long cfg) {

    unsigned long port = pin>>8;
    int pin_bit = pin&0xff;

    enableWritingPmnPFS();

    PmnPFS(port,pin_bit) = cfg;

    disableWritingPmnPFS();
}  

#endif /* PIN_CONFIG_H */
