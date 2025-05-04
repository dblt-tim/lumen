MAKEFLAGS += -rR
.SUFFIXES:

# USER CONTROLLABLE FLAGS AND VARIABLES

# SYSTEM ARCH

ARCH = x86_64

CFLAGS = -g -O2 -pipe
CPPFLAGS = 
NASMFLAGS = -F dwarf -g
LDFLAGS = 

override OUTPUT := lumen

TOOLS = ../tools/bin

CC = $(TOOLS)/$(ARCH)-elf-gcc
# -------------------------------------

override CFLAGS += \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-PIC \
    -m64 \
    -march=x86-64 \
    -mno-80387 \
    -mno-mmx \
    -mno-sse \
    -mno-sse2 \
    -mno-red-zone \
    -mcmodel=kernel

override CPPFLAGS := \
    -I source \
    $(CPPFLAGS) \
    -DLIMINE_API_REVISION=3 \
    -MMD \
    -MP

override NASMFLAGS += \
    -Wall \
    -f elf64

override LDFLAGS += \
    -Wl,-m,elf_x86_64 \
    -Wl,--build-id=none \
    -nostdlib \
    -static \
    -z max-page-size=0x1000 \
    -T arch/$(ARCH)-link.ld

override SRCFILES := $(shell cd source && find -L * -type f | LC_ALL=C sort)
override CFILES := $(filter %.c,$(SRCFILES))
override ASFILES := $(filter %.S,$(SRCFILES))
override NASMFILES := $(filter %.asm,$(SRCFILES))
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))

.PHONY: all
all: bin/$(OUTPUT)

bin/$(OUTPUT): arch/$(ARCH)-link.ld $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@

obj/%.c.o: source/%.c
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	
obj/%.S.o: source/%.S
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

obj/%.asm.o: source/%.asm
	mkdir -p "$$(dirname $@)"
	nasm $(NASMFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf bin obj
