#pragma once

#define BIT_RANGE(instr,upper,lower) (instr & (((1 << (upper-lower+1)) - 1) << lower))
#define BIT_SINGLE(instr,pos) (instr & (1 << pos))
