CC=gcc
CFLAGS=-Wall -g

mips: emulator.o instruction.o regs.o operation.o memmgr.o cache.o memspy.o ram.o memutils.o
	$(CC) $(CFLAGS) emulator.o instruction.o regs.o operation.o ram.o memmgr.o cache.o memspy.o memutils.o -lm -fPIC -shared -o libmips.so  

main: cmd/main.c cmd/cases.c cmd/bench.c cmd/bench.h cmd/cases.h mips
	$(CC) $(CFLAGS) -L . cmd/cases.c cmd/main.c cmd/bench.c -lmips -o main

instruction.o: mips/instruction.c mips/instruction.h
	$(CC) $(CFLAGS) -c -fPIC mips/instruction.c

regs.o: mips/regs.c mips/regs.h
	$(CC) $(CFLAGS) -c -fPIC mips/regs.c

operation.o: mips/operation.c mips/operation.h mips/regs.o mips/instruction.o
	$(CC) $(CFLAGS) -c -fPIC mips/operation.c 

memmgr.o: mem/memmgr.c mem/memmgr.h cache.o memspy.o ram.o
	$(CC) $(CFLAGS) -c -fPIC mem/memmgr.c

cache.o: mem/cache.c mem/cache.h 
	$(CC) $(CFLAGS) -c -fPIC mem/cache.c 

ram.o: mem/ram.c mem/ram.h
	$(CC) $(CFLAGS) -c -fPIC mem/ram.c

memutils.o: mem/memutils.c mem/memutils.h ram.o
	$(CC) $(CFLAGS) -c -fPIC mem/memutils.c

memspy.o: mem/memspy.c mem/memspy.h
	$(CC) $(CFLAGS) -c -fPIC mem/memspy.c

emulator.o: mips/emulator.c mips/emulator.h instruction.o regs.o operation.o
	$(CC) $(CFLAGS) -c -fPIC mips/emulator.c

.PHONY: clean
clean:
	rm -rf *.o *.so