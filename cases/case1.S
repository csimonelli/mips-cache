# Benchmark B0 
#include <regdef.h>
#include <sys/asm.h>
#include <sys/syscall.h>

        .text
        .align  5
        .globl  main
        .ent    main

main:
        li      t1, 100 
loop: 
        lw      t2, 1024(zero) 
        subu    t1, t1, 1 
        bnez    t1, loop

out:
        b       out
        
        .end    main




main:
 000:	24090064 	li	t1,100
loop: 
 004:	8c0a0400 	lw	t2,1024(zero)
        1000 1100
        
        1111 1000
        f  
        0011 1100

 008:	2529ffff 	addiu	t1,t1,-1
 00c:	1520fffd 	bnez	t1,004 <loop>
 010:	00000000 	nop
out:
 014:	ffffffff 	dump
fin:
 018:	1000ffff 	b	7e0 <fin>
 01c:	00000000 	nop
 020:	00000000 	nop



 0x24090064
 0x8c0a0400
 0x2529ffff
 0x1520fffd
 0x00000000
 0xffffffff
 0x1000ffff
 0x00000000
 0x00000000


case 5
0x24090064
0x8c0a0404
0x8c0a0408
0x8c0a040c
0x8c0a0410
0x2529ffff
0x1520fff9
0x00000000
0xffffffff
0x1000ffff
0x00000000
0x00000000