# Name: Makefile
# Project: HIDKeys
# Author: Christian Starkjohann
# Creation Date: 2006-02-02
# Tabsize: 4
# Copyright: (c) 2006 by OBJECTIVE DEVELOPMENT Software GmbH
# License: Proprietary, free under certain conditions. See Documentation.
# This Revision: $Id: Makefile,v 1.7 2008-09-13 18:34:09 raph Exp $

UISP = uisp -dprog=stk500 -dpart=atmega8 -dserial=/dev/ttyS1
COMPILE = avr-gcc -Wall -Os -Iusbdrv -I. -mmcu=atmega8 -DF_CPU=16000000L #-DDEBUG_LEVEL=1
COMMON_OBJS = usbdrv/usbdrv.o usbdrv/usbdrvasm.o usbdrv/oddebug.o main.o
HEXFILE=main.hex

OBJS = $(COMMON_OBJS) snes.o snesmouse.o nes.o db9.o devdesc.o tg16.o segamtap.o


# symbolic targets:
all:	$(HEXFILE)

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@


clean:
	rm -f $(HEXFILE) main.lst main.obj main.cof main.list main.map main.eep.hex main.bin *.o usbdrv/*.o main.s usbdrv/oddebug.s usbdrv/usbdrv.s

# file targets:
main.bin:	$(OBJS)	snes.o nes.o snesmouse.o db9.o tg16.o devdesc.o 
	$(COMPILE) -o main.bin $(OBJS) -Wl,-Map=main.map

$(HEXFILE):	main.bin
	rm -f $(HEXFILE) main.eep.hex
	avr-objcopy -j .text -j .data -O ihex main.bin $(HEXFILE)
	./checksize main.bin

#flash:	all
#	$(UISP) --erase --upload --verify if=$(HEXFILE)

flash:
	avrdude -c buspirate speed=7 -P com11 -p m8 -U flash:w:$(HEXFILE)
	
#sudo avrdude -p m8 -P usb -c avrispmkII -Uflash:w:$(HEXFILE) -B 1.0

# Fuse high byte:
# 0xc9 = 1 1 0 0   1 0 0 1 <-- BOOTRST (boot reset vector at 0x0000)
#        ^ ^ ^ ^   ^ ^ ^------ BOOTSZ0
#        | | | |   | +-------- BOOTSZ1
#        | | | |   + --------- EESAVE (don't preserve EEPROM over chip erase)
#        | | | +-------------- CKOPT (full output swing)
#        | | +---------------- SPIEN (allow serial programming)
#        | +------------------ WDTON (WDT not always on)
#        +-------------------- RSTDISBL (reset pin is enabled)
# Fuse low byte:
# 0x9f = 1 0 0 1   1 1 1 1
#        ^ ^ \ /   \--+--/
#        | |  |       +------- CKSEL 3..0 (external >8M crystal)
#        | |  +--------------- SUT 1..0 (crystal osc, BOD enabled)
#        | +------------------ BODEN (BrownOut Detector enabled)
#        +-------------------- BODLEVEL (2.7V)
fuse:
	avrdude -c buspirate speed=7 -P com11 -p m8 -U lfuse:w:0xff:m -U hfuse:w:0xc9:m
	#$(UISP) --wr_fuse_h=0xc9 --wr_fuse_l=0x9f

#fuse_usb:
#	sudo avrdude -p m8 -P usb -c avrispmkII -Uhfuse:w:0xc9:m -Ulfuse:w:0x9f:m -B 10.0

