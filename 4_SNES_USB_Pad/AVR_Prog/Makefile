#AVR-GCC Makefile
PROJECT=hello
SOURCES=hello.c
CC=avr-gcc
OBJCOPY=avr-objcopy
#angabe des ziels für avr-libc
MMCU=atmega8
CFLAGS=-mmcu=$(MMCU) -Wall

$(PROJECT).hex: $(PROJECT).out
		$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
		$(CC) $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)

########################optional###############################
install: $(PROJECT).hex
		avrdude -c buspirate speed=7 -P com11 -p $(MMCU) -U flash:w:$(PROJECT).hex
clean:
		rm -f $(PROJECT).out
		rm -f $(PROJECT).hex
		
#fuses
#atmega8 16MHz external crystal
#
fuse:
		avrdude -c buspirate speed=7 -P com11 -p $(MMCU) -U lfuse:w:0xff:m -U hfuse:w:0xc9:m