#ifndef RA4M1_H
#define RA4M1_H


#define PCNTR1(port) *((volatile unsigned long *)(0x40040000 + 0x20*port))
#define PCNTR3(port) *((volatile unsigned long *)(0x40040008 + 0x20*port))
#define PmnPFS(port, pin) *((volatile unsigned long *)(0x40040800 + 0x40*port + 4*pin))
#define PWPR *((volatile unsigned char *)(0x40040d03))
#define VTOR *((volatile unsigned long *)0xE000ED08)

// Serial Communications Interface (SCI)
typedef struct {
    volatile unsigned char SMR;
    volatile unsigned char BRR;
    volatile unsigned char SCR;
    volatile unsigned char TDR;
    volatile unsigned char SSR;
    volatile unsigned char RDR;
    volatile unsigned char SCMR;
    volatile unsigned char SEMR;
    volatile unsigned char SNFR;
    volatile unsigned char SIMR1;
    volatile unsigned char SIMR2;
    volatile unsigned char SIMR3;
    volatile unsigned char SISR;
    volatile unsigned char SPMR;
    volatile unsigned short TDRHL;
    volatile unsigned short RDRHL;
    volatile unsigned char MDDR;
    volatile unsigned char DCCR;
    volatile unsigned short FCR;
    volatile unsigned short FDR;
    volatile unsigned short LSR;
    volatile unsigned short CDR;
    volatile unsigned char SPTR;
} SCI_Type;

#define SCI(n)   ((volatile SCI_Type *)(0x40070000 + n*0x20))

#define R_MSTP_MSTPCRB         *((volatile unsigned long *) 0x40047000UL)
#define BSP_MSTP_REG_FSP_IP_SCI(channel)        R_MSTP_MSTPCRB
#define BSP_MSTP_BIT_FSP_IP_SCI(channel)        (1U << (31U - channel));

__attribute__((always_inline)) static inline unsigned long __get_PRIMASK(void)
{
    unsigned long result;

    __asm volatile ("MRS %0, primask" : "=r" (result) );
    return(result);
}

__attribute__((always_inline)) static inline void __set_PRIMASK(unsigned long priMask)
{
    __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}

#endif /* RA4M1_H */    
