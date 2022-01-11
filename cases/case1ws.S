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
	    sw      t2, 1028(zero) 
        subu    t1, t1, 1 
        bnez    t1, loop

out:
        b       out
        
        .end	main



main:
 7c0:	24090064 	li	t1,100
 7c4:	8c0a0400 	lw	t2,1024(zero)
 7c8:	ac0a0404 	sw	t2,1028(zero)
 7cc:	2529ffff 	addiu	t1,t1,-1
 7d0:	1520fffc 	bnez	t1,7c4 <loop>
 7d4:	00000000 	nop
 7d8:	1000ffff 	b	7d8 <out>
 7dc:	00000000 	nop
