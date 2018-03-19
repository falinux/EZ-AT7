#
#  ezload 메이크 화일 
#

#------------------------------------------------------------------------------------
# 아래 영역을 적당히 수정하쇼!!!
#------------------------------------------------------------------------------------
TARGET     = ezload_usb

SRCS =  
ASMS =  

ASMS += start.S 
ASMS += lib1funcs.S

SRCS += main.c 
SRCS += console.c 
SRCS += timer.c 
SRCS += printf.c 
SRCS += vsprintf.c 
SRCS += string.c 
SRCS += mem_edit.c 
SRCS += xmodem.c
SRCS += crc16.c
SRCS += vscanf.c 
SRCS += flash.c 
SRCS += irq.c
SRCS += usb_serial.c

#------------------------------------------------------------------------------------

IMAGE      = $(TARGET).bin
PRE_TARGET = $(TARGET)-elf32

ASM_OBJS  = $(ASMS:%.S=%.o)		
C_OBJS    = $(SRCS:%.c=%.o)		

OBJS = $(ASM_OBJS) $(C_OBJS)

CC = arm-linux-gcc
LD = arm-linux-ld
OC = arm-linux-objcopy

TOPDIR	:= $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
INCLUDES = -I. -I$(TOPDIR)/include 

CFLAGS    = -nostdinc $(INCLUDES)
CFLAGS   += -Wall -Wstrict-prototypes -Wno-trigraphs -Os
CFLAGS   += -fno-strict-aliasing -fno-common -fno-zero-initialized-in-bss 
CFLAGS   += -march=armv4t -mtune=arm7tdmi -malignment-traps -msoft-float -fno-builtin

OCFLAGS = -O binary -R .note -R .comment -S

#LDFLAGS    = -static -nostdlib -nostartfiles -nodefaultlibs -p -X -T ./ezload-ld-script
LDFLAGS    = -static -nostdlib -nostartfiles -nodefaultlibs -p -X -T ./ezload-ld-script -Map=ezload.map

#
# Compilation target for C++ files
#

all : $(PRE_TARGET)
	$(OC) $(OCFLAGS)  $(PRE_TARGET) $(IMAGE)

$(PRE_TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $@  $(OBJS)

dep :
	$(CC) -M $(INCLUDES) $(SRCS) > .depend

clean:
	rm -f *.o
	rm -f *.bak
	rm -f *.map
	rm -f $(PRE_TARGET)
	rm -f $(IMAGE)

distclean: clean
	rm -rf .depend	

%.o:%.S
	@echo "Assembler compiling $< ..."
	$(CC) -c $(CFLAGS) -D__ASSEMBLY__ -o $@ $<


%.o:%.c
	@echo "Compiling $< ..."
	$(CC) -c $(CFLAGS) -o $@ $<

ifeq (.depend,$(wildcard .depend))
include .depend
endif
