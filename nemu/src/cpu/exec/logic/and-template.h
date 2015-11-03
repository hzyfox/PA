#include "cpu/exec/template-start.h"

#define instr and

static void do_execute () {
	DATA_TYPE result = op_dest->val & op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	cpu.CF=0;
    cpu.OF=0;
    if(result<=0) cpu.SF=1;
    else cpu.SF=0;
        if(result==0) cpu.ZF=1;
        else cpu.ZF=0;
        if((op_dest->val&0xf)-(op_src->val&0xf)<0) cpu.AF=1;
        else cpu.AF=0;
        if(((result&0x80)^(result&0x40)^(result&0x20)^(result&0x10)^(result&0x8)^(result&0x4)^(result&0x2)^(result&0x1))==0)
        cpu.PF=1;
        else cpu.PF=0;

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
