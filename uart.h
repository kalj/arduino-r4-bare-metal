#ifndef UART_H
#define UART_H

void uartSetup(long sciIdx);
void uartWriteChar(long sciIdx, char c);
void uartWriteStr(long sciIdx, const char *src);

#endif /* UART_H */
