### Makefile.tpl - 
## 
## Author: Karl Ljungkvist

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
BOSSAC=/home/kalle/.arduino15/packages/arduino/tools/bossac/1.9.1-arduino5/bossac
# BOSSAC=bossac
CFLAGS=-Wall -Wextra -pedantic -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fno-builtin -std=c2x -nostdlib
LINK_SCRIPT=link.ld
ELF=firmware.elf
BIN=firmware.bin
OBJS=startup.o main.o uart.o gpio.o modules.o led_matrix.o
SRC=

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(OBJS) $(LINK_SCRIPT)
	$(CC) -T $(LINK_SCRIPT) -nostdlib $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	$(RM) $(BIN) $(ELF) $(OBJS)

flash: $(BIN)
	stty -F /dev/ttyACM0 1200 && sleep 0.5 && $(BOSSAC) -d --port=ttyACM0 -U -e -w $(BIN) -R

### Makefile ends here
