#include "uart.h"

#include "modules.h"
#include "pin_config.h"

void uartSetup(long sciIdx) {

    long tx_pin;
    long rx_pin;
    long psel_uart;
    if(sciIdx == 2) {
        tx_pin= 0x301;
        rx_pin= 0x302;
        psel_uart = 0x4;
    } else if(sciIdx == 9) {
        tx_pin= 0x301;
        rx_pin= 0x302;
        psel_uart = 0x5;
    } else {
        // error
        while(1) {}
    }

    // Set IO port functions
    configPin(rx_pin,(psel_uart<<24)|(1<<16)); // PSEL=0x4, Use as peripheral
    configPin(tx_pin,(psel_uart<<24)|(1<<16)); // PSEL=0x4, Use as peripheral

    enable_module_sci(sciIdx);

    SCI(sciIdx)->SCR   = 0U;
    SCI(sciIdx)->SSR   = 0U;
    SCI(sciIdx)->SIMR1 = 0U;
    SCI(sciIdx)->SIMR2 = 0U;
    SCI(sciIdx)->SIMR3 = 0U;
    SCI(sciIdx)->CDR   = 0U;

    SCI(sciIdx)->DCCR = (1 << 6); // IDSEL compare data when the MPB bit is 1 (ID frame) only.
    SCI(sciIdx)->SPTR = (1 << 1) // SPB2DT: Output high on TXDn pin
        | (1 << 2);          // SPB2IO: The value of SPB2DT bit is output to TXDn pin
    SCI(sciIdx)->SMR = (0b00 << 0) // CKS: PCLK clock / 1
        | (0 << 2)             // MP: multi-processor disabled
        | (0 << 3)             // STOP: 1 stop bits
        | (0b00 << 4)          // PM,PE: Parity not added,
        | (0b0 << 6)           // CHR: (CHR1 CHR: 1 0 - 8-bit length)
        | (0b0 << 7);          // CM: asynchronous mode
    SCI(sciIdx)->SCMR = 0b01100010 // reserved bits
        | (0 << 0) // SMIF: non-smart card interface mode
        | (0 << 2) // SINV: TDR and RDR not inverted
        | (0 << 3) // SIDR: LSB first
        | (1 << 4) // CHR1: (CHR1 CHR: 1 0 - 8-bit length)
        | (1 << 7); // BCP2: doesn't matter in non-smart card mode
    SCI(sciIdx)->SPMR = 0;
    SCI(sciIdx)->SNFR = 0; // NOISE_CANCEL_LVL1;
    SCI(sciIdx)->BRR = 155;
    SCI(sciIdx)->MDDR = 0;
    SCI(sciIdx)->SEMR = (0 << 2) // BRME: bit rate modulation function disabled
        | (0 << 3)           // BCSE: BGDM and ABCS determins clock cycle for 1-bit period
        | (0 << 4)           // ABCS: selects 16 base clock cycles for 1-bit period
        | (0 << 5)           // NFEN: noise filter for RXDn disabled
        | (0 << 6)           // BGDM: baud gen double freq disabled
        | (0 << 7);          // RXDESEL: low level on RXDn is detected as the start bit
    SCI(sciIdx)->SCR = (0b00 << 0) // CKE: on-chip baud rate generator
        |(1 << 4)              // RE: Receive enabled
        |(1 << 5);             // TE: Transmit enabled

#if 0

    /* SCR(sciIdx) = 0; */
    SCI(sciIdx)->SCR = 0;
    SIMR1(sciIdx) = 0; // Set SIMR1.IICM to 0                                - Arduino same
    /* Set SPMR.CKPH and SPMR.CKPOL to 0 */
    SMR(sciIdx) = 0; // default    - PCLKA/1 , n=0                           - Arduino same
    SCMR(sciIdx) = 0xf2; // default LSB first, 8-bit char BCP2=1             - Arduino same
    SEMR(sciIdx) = 0; // default - BRME=0, ABCSE=0, ABCS=0, BGDM=0           - Arduino bits 2,7 set i.e. BRME=1 and RXDESEL=1

    BRR(sciIdx) = 155; // 155.25 is exact                                    - Arduino 140
    /* MDDR is irrelevant since SEMS.BRME=0 */

    /* SCR(sciIdx) |= (1<<4)|(1<<5); // Enable Receive and Transmit 0;          - Arduino bits 4,5,6 set */
    SCI(sciIdx)->SCR = (1<<5); // Enable Transmit;          - Arduino bits 4,5,6 set
#endif
}

void uartWriteChar(long sciIdx, char c) {
    SCI(sciIdx)->TDR = c;
    while((SCI(sciIdx)->SSR & (1<<2)) == 0) {}
}    

void uartWriteStr(long sciIdx, const char *src) {
    while (*src != 0) {
        uartWriteChar(sciIdx, *src);
        src++;
    }
}    
