#ifndef GPIO_H
#define GPIO_H

typedef enum {
    PIN_MODE_INPUT = 0,
    PIN_MODE_OUTPUT = 1
} PinMode;  

typedef enum {
    PIN_LEVEL_LOW = 0,
    PIN_LEVEL_HIGH = 1
} PinLevel;


void setPinMode(unsigned long pin, PinMode mode);

void setPinValue(unsigned long pin, PinLevel lvl);

#endif /* GPIO_H */
