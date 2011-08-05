
## Created by Anjuta
MCU = atmega128
TARGET = ISP
F_CPU = 16000000UL

## Optimization can be
#  0, 1, 2, 3, s
OPT = s

CSRC = isp.c
CSRC += ../lib/utils.c
CSRC += ../lib/usart.c
CSRC += ../lib/spi.c

## Format can be
# ihex, binary, srec
FORMAT = ihex

CSTANDARD = gnu99

DEBUG = dwarf-2

## Enter programmer hardware
#  For a full list enter
#  avrdude -c?
AVRDUDE_PROGRAMMER = avrisp2

## Enter Baudrate 
#  Only for serial programmers or FastBoot
PROGRAMMER_BAUDRATE = 9600

## Enter Communication Port
#  Examples:
#  usb
#  /dev/ttyS0
PROGRAMMER_PORT = usb

Ext_lib_path= ../lib/
EXTRAINCDIRS = . $(Ext_lib_path)


CC = avr-gcc
CFLAGS = -mmcu=$(MCU)
CFLAGS += -DF_CPU=$(F_CPU)
CFLAGS += -std=$(CSTANDARD)
CFLAGS += -g$(DEBUG) 
CFLAGS += -O$(OPT)
CFLAGS += -Werror -Wall -Wextra -Wstrict-prototypes
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
#CFLAGS += -Wa,-adhlns=$(<:.c=.lst)

# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

ALL_CFLAGS = $(CFLAGS) $(GENDEPFLAGS)


OBJECTS = $(CSRC:.c=.o)
INCFLAGS = 
LDFLAGS = -Wl,-Map=$(TARGET).map,--cref
LIBS = 

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump
SIZE           = avr-size
SHELL          = sh
REMOVE         = rm -f
COPY           = cp

all: build

build: elf hex eep

elf: $(TARGET).elf
hex: $(TARGET).hex
eep: $(TARGET).eep

$(TARGET).elf: $(OBJECTS)
	$(CC) $(ALL_CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

.SUFFIXES:
.SUFFIXES:	.c .cc .C .cpp .o

# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)

# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

%.eep: %.elf
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Compile: create object files from C source files.
%.o : %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@

count:
	wc *.c *.cc *.C *.cpp *.h *.hpp

# Target: clean project.
clean: 
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) .dep/*
    
install:
	avrdude -p$(MCU) -P$(PROGRAMMER_PORT) -c$(AVRDUDE_PROGRAMMER) -b$(PROGRAMMER_BAUDRATE) -U flash:w:$(TARGET).hex


# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


.PHONY: all
.PHONY: count
.PHONY: clean
