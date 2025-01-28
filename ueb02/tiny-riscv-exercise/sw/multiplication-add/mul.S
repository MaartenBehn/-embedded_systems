.globl _start
_start:
    li a0,50 
    li a1,100
    li a2,0        # Result
    li a3,0        # Counter

loop:              # Loop a0 times
    bge a3,a0,end  
    add a2,a2,a1   # Add a1 to a2 in every loop
    addi a3,a3,1   # Increase Counter
    j loop

end:
    mv a0,a2       # Move Result into a0
    li a7,93       # Set exit syscall
    ecall


# Runtime Complexity: 
# O( a0 * 4 + 8 ) => O( a0 ) => O(n)