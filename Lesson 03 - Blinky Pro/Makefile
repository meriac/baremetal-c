PROJECT:=blinky_pro

# shared directory between lessons
COMMON:=../Common

# all source files used for compiling applicaton
SOURCES:= \
	$(PROJECT).c \
	$(COMMON)/Helper/helper_irq.c

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

# derived variables
OBJECTS:=$(SOURCES:.c=.o)

.PHONY: all

all: $(PROJECT).asm $(PROJECT).bin

%.bin: %.elf
	$(OBJCOPY) $< -O binary $@

%.asm: %.elf
	$(OBJDUMP) -S $< > $@

$(PROJECT).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.elf *.bin *.asm *.hex $(OBJECTS)
