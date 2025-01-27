.globl _start
_start:

li a0,42
li a7,1
ecall

li a0,97
li a7,2
ecall

li a0,97
li a7,2
ecall

end:
li a7,93
li a0,0
ecall

