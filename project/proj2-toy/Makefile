# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: projToy.elf 

#additional rules for files
projToy.elf: ${COMMON_OBJECTS} Main.o stateMachines.o switches.o led.o assem.o buzzer.o wdInterruptHandler.o p1_interrupt_handler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: projToy.elf
	msp430loader.sh projToy.elf

clean:
	rm -f *.o *.elf

led.o: led.c led.h

assem.o: stateMachines.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h stateMachines.h
