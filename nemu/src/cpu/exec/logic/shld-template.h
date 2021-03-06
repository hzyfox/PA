#include "cpu/exec/template-start.h"

#define instr shld

#if DATA_BYTE == 2 || DATA_BYTE == 4
static void do_execute () {
	DATA_TYPE in = op_dest->val;
	DATA_TYPE out = op_src2->val;

	uint8_t count = op_src->val;
	count &= 0x1f;
	while(count != 0) {
		cpu.CF = (out >> ((DATA_BYTE << 3) - 1)) & 1;
		out <<= 1;
		out |= (in >> ((DATA_BYTE << 3) - 1)) & 1;
		in <<= 1;
		count --;
	}

	cpu.SF = (out >> ((DATA_BYTE << 3) - 1)) & 1;
	cpu.ZF = out ? 0 : 1;
	uint8_t low_b = out & 0xff;
	cpu.PF = !((low_b & 0x01)^(low_b>>1 & 0x01)^(low_b>>2 & 0x01)^(low_b>>3 & 0x01)^(low_b>>4 & 0x01)^(low_b>>5 & 0x01)^(low_b>>6 & 0x01)^(low_b>>7 & 0x01));

	OPERAND_W(op_src2, out);

	print_asm("shld" str(SUFFIX) " %s,%s,%s", op_src->str, op_dest->str, op_src2->str);
}

make_helper(concat(shldi_, SUFFIX)) {
	int len = concat(decode_si_rm2r_, SUFFIX) (eip + 1);  /* use decode_si_rm2r to read 1 byte immediate */
	op_dest->val = REG(op_dest->reg);
	do_execute();
	return len + 1;
}
#endif

#include "cpu/exec/template-end.h"