#ifndef __FLOAT_H__
#define __FLOAT_H__

#include "trap.h"

typedef int FLOAT;

static inline int F2int(FLOAT a) {
	//nemu_assert(0);
       /* we abadon the decimals,means: we just transfer the  part of interger*/
     if((a&0x80000000)==0)
	return (a>>16)&0x7FFF;
     else
	return -((a>>16)&0x7FFF);
}

static inline FLOAT int2F(int a) {
	//nemu_assert(0);
	return (FLOAT)a*65536;
}

static inline FLOAT F_mul_int(FLOAT a, int b) {
	nemu_assert(0);
	return (FLOAT)(a*b);
}

static inline FLOAT F_div_int(FLOAT a, int b) {
	nemu_assert(0);
	return (FLOAT)(a/b);
}

FLOAT f2F(float);
FLOAT F_mul_F(FLOAT, FLOAT);
FLOAT F_div_F(FLOAT, FLOAT);
FLOAT Fabs(FLOAT);
FLOAT sqrt(FLOAT);
FLOAT pow(FLOAT, FLOAT);

#endif
