
int main();

extern void _STACK_END(void);

__attribute__((naked, noreturn)) void _reset(void)
{
    extern long _BSS_START, _BSS_END, _DATA_START, _DATA_END, _DATA_LOAD_ADDRESS;
    // memset .bss to zero
    for (long *dst = &_BSS_START; dst < &_BSS_END; dst++) *dst = 0;
    // copy .data section to RAM region
    for (long *dst = &_DATA_START, *src = &_DATA_LOAD_ADDRESS; dst < &_DATA_END;) *dst++ = *src++;

    main();
    for(;;) (void) 0;
}

/* __attribute__((section(".vectors"))) void (*const tab[16 + 91])(void) = { */
typedef void voidFunc(void);
__attribute__((section(".vectors")))  voidFunc * const tab[16 + 91] = {
  _STACK_END, _reset
};
