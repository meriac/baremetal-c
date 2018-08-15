PROJECT:=blinky

# shared directory between lessons
COMMON:=../Common

# toolchain settings
CROSS:=arm-none-eabi-
CC:=$(CROSS)gcc
OBJDUMP:=$(CROSS)objdump
OBJCOPY:=$(CROSS)objcopy

# gcc & ld compiler flags
OPT:=-Og
FLAGS:=-mcpu=cortex-m4 -mthumb
CFLAGS:=$(FLAGS) $(OPT) -I$(COMMON)/Include -I$(COMMON)/Include/CMSIS5 -fno-common -g3 -Wall -Werror -Wextra
LDFLAGS:=$(FLAGS) -T$(COMMON)/Linker/minimal.ld -nostartfiles -nostdlib -lnosys

.PHONY: all

all: $(PROJECT).asm $(PROJECT).bin

%.bin: %.elf
	$(OBJCOPY) $< -O binary $@

%.asm: %.elf
	$(OBJDUMP) -S $< > $@

%.elf: %.o
	$(CC) $(LDFLAGS) -o $@ $<

clean:
	rm -f *.elf *.bin *.asm *.hex
