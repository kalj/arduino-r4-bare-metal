#include "led_matrix.h"

#include "gpio.h"

typedef unsigned long uint32_t;

const static uint32_t  ledMatrixPins[] = {
    (0<<8) |3,
    (0<<8) |4,
    (0<<8) |11,
    (0<<8) |12,
    (0<<8) |13,
    (0<<8) |15,
    (2<<8) |4,
    (2<<8) |5,
    (2<<8) |06,
    (2<<8) |12,
    (2<<8) |13,
};


const static uint32_t ledMatrix[][2] = {
    {7,3}, {3,7},

    {7,4}, {4,7},
    {3,4}, {4,3},

    {7,8}, {8,7},
    {3,8}, {8,3},
    {4,8}, {8,4},

    {7,0}, {0,7},
    {3,0}, {0,3},
    {4,0}, {0,4},
    {8,0}, {0,8},

    {7,6}, {6,7},
    {3,6}, {6,3},
    {4,6}, {6,4},
    {8,6}, {6,8},
    {0,6}, {6,0},

    {7,5}, {5,7},
    {3,5}, {5,3},
    {4,5}, {5,4},
    {8,5}, {5,8},
    {0,5}, {5,0},
    {6,5}, {5,6},

    {7,1}, {1,7},
    {3,1}, {1,3},
    {4,1}, {1,4},
    {8,1}, {1,8},
    {0,1}, {1,0},
    {6,1}, {1,6},
    {5,1}, {1,5},

    {7,2}, {2,7},
    {3,2}, {2,3},
    {4,2}, {2,4},
    {8,2}, {2,8},
    {0,2}, {2,0},
    {6,2}, {2,6},
    {5,2}, {2,5},
    {1,2}, {2,1},

    {7,10}, {10,7},
    {3,10}, {10,3},
    {4,10}, {10,4},
    {8,10}, {10,8},
    {0,10}, {10,0},
    {6,10}, {10,6},
    {5,10}, {10,5},
    {1,10}, {10,1},
    {2,10}, {10,2},

    {7,9}, {9,7},
    {3,9}, {9,3},
    {4,9}, {9,4},
};

void led_matrix_reset()
{
    for(int i=0; i<sizeof(ledMatrixPins)/sizeof(ledMatrixPins[0]); i++)
    {
        setPinMode(ledMatrixPins[i], PIN_MODE_INPUT);
    }
}

void led_matrix_pinon(int i)
{
    uint32_t highPin = ledMatrixPins[ledMatrix[i][0]];
    uint32_t lowPin = ledMatrixPins[ledMatrix[i][1]];
    setPinMode(highPin, PIN_MODE_OUTPUT);
    setPinMode(lowPin, PIN_MODE_OUTPUT);
    setPinValue(highPin, PIN_LEVEL_HIGH);
    setPinValue(lowPin, PIN_LEVEL_LOW);
}

void led_matrix_pinoff(int i)
{
    uint32_t highPin = ledMatrixPins[ledMatrix[i][0]];
    uint32_t lowPin = ledMatrixPins[ledMatrix[i][1]];
    setPinMode(highPin, PIN_MODE_INPUT);
    setPinMode(lowPin, PIN_MODE_INPUT);
}
