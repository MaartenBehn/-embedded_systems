.globl _start
_start:
	li a0,7        # base
	li a1,10	   # factor
    li a3,0        # Counter
	mv a2,a0	   # Result
	addi a1,a1,-1  # Remove one from a1 because Result starts with value of a0

loop:              # Loop a0 times
    bge a3,a1,end  
    mul a2,a2,a0   # Mul a0 to a2 in every loop
    addi a3,a3,1   # Increase Counter
    j loop

end:
	mv a0,a2       # Move Result into a0
	li a7,93
	ecall
