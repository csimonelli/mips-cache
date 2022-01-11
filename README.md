A mips (Microprocessor without Interlocked Pipeline Stages) lib emulator.

# Operations implemented:
* nop
* addu
* slt
* beq
* bneq
* addiu
* lw
* sw
* end
* dump

*"Dump" and "end" are not in the mips instruction code.

end: Stops the simulation.

dump: Shows the value of the virtual microprocessor registers.

# Cache: 

## All cache configs ar implemented:
    
* Full associative
* Set associative
* Direct maped.

## Write strategies implemented:
* Write through
* write back

Custom eviction policy could be provided (for full association and set associative)

# Reference program.
In CMD there is a reference program with some fun cases to check for some problems that your program could incur depending only on the cache architecture.

If you want to test the lib usig the test program in CMD remember to add the directory where the lib is placed to the LD_LIBRARY_PATH

export LD_LIBRARY_PATH=YOUR_LIB_PATH:$LD_LIBRARY_PATH 

# Almost known issues:
At some point I got tired of freeing up memory. There are TODOs in those cases.

Bytes (not words) setting in cache is not tested, and I'm pretty sure this doesn't work.

# Future: 

Pipeline

Virtual memory