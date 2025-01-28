.globl _start
_start:

li a0,50
li a1,100

mul a0,a0,a1

li a7,93
ecall

# Runtime Complexity: 
# O( 5 ) => O( 1 )

# The Runtime Complexity would only alos be O(1) if the processor would have an hardware implementation for multiplication. 
# Sometimes its the case that there is a mul instruction for the processor but the mul is still calculated by addition, 
# or at least will take longer than one clock cycle.