#include "uart.h"
#include "gpio.h"
#include "led_matrix.h"

#include "ra4m1.h"

typedef unsigned long uint32_t;
typedef unsigned char uint8_t;

static const char *msg = "HELO\n";

void doNops(long n) {
    for(volatile long i=0; i<n; i++) (void)0;
}

char nibble_to_hex(unsigned int n)
{
    return n<10 ? '0'+n : 'a'+(n-10);
}

void print_hex_u32(long sci_idx, unsigned long u)
{
    char buf[11];
    buf[0] = '0';
    buf[1] = 'x';
    for(int i=0; i<8; i++)
    {
        buf[2+i] = nibble_to_hex((u >> (4*(7-i)))&0xf);
    }
    buf[10] = '\0';

    uartWriteStr(sci_idx, buf);
}


void print_dec_int(long sci_idx, int d)
{
    char buf[11];
    int ndig = 0;
    int d2 = d;
    while(d2 != 0)
    {
        ndig++;
        d2 /= 10;
    }
    for(int i=0; i<ndig; i++)
    {
        int dig = d % 10;
        buf[ndig-1-i] = '0'+dig;
        d /= 10;
    }
    buf[ndig] = '\0';

    if(ndig == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
    }

    uartWriteStr(sci_idx, buf);
}

uint8_t frame_buffer[8*12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
    1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0,
    1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0,
    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0,
    1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0,
    1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0,
};

int main() {

    unsigned long vtor = VTOR;

    /* set P102 to output */
    long led_pin = 0x102;

    /* setPinMode(led_pin, PIN_MODE_OUTPUT); */

    long sci_idx=2;
    uartSetup(sci_idx);

    uartWriteStr(sci_idx, "VTOR: ");
    print_hex_u32(sci_idx, vtor);
    uartWriteChar(sci_idx, '\n');


    /*
    uartWriteStr(sci_idx, "Config area bit map:\n");
    long *config_area_bit_map_base = (long *)0x01010008;
    for(int i=0; i<11; i++)
    {
        long val = config_area_bit_map_base[i];
        print_hex_u32(sci_idx, val);
        uartWriteChar(sci_idx, '\n');
    }
    */

    /* while (1) */
    /* {        */
    /*     uartWriteStr(sci_idx, msg); */

    /*     // set P102 to high */
    /*     setPinValue(led_pin, PIN_LEVEL_HIGH); */
    /*     doNops(999999); */
    
    /*     // set P102 to low */
    /*     setPinValue(led_pin, PIN_LEVEL_LOW); */
    /*     doNops(999999); */
    /* } */

    setPinMode(led_pin, PIN_MODE_OUTPUT);


    while(1) {
        for(int y=0; y<8; y++)
        {
            for(int x=0; x<12; x++)
            {

                int i = y*12+x;
                if(frame_buffer[i])
                {
                    led_matrix_pinon(i);
                    doNops(999);
                    led_matrix_pinoff(i);
                }
            }
        }
    }

    while (1)
    {
        uartWriteStr(sci_idx, msg);

        // set P102 to high
        setPinValue(led_pin, PIN_LEVEL_HIGH);
        doNops(999999);
    
        // set P102 to low
        setPinValue(led_pin, PIN_LEVEL_LOW);
        doNops(999999);
    }

    return 0;
}  
