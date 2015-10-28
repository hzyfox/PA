#include "cpu/exec/template-start.h"
#include "cpu/reg.h"
#define instr test


static void do_execute(){
    DATA_TYPE result=op_dest->val&op_src->val;
    cpu.CF=0;
    cpu.OF=0;
    int PF_flag=0;

    if(result<=0)
        cpu.SF=1;
        else if(result>0)
        cpu.SF=0;
    if(result==0)
        cpu.ZF=1;
    else cpu.ZF=0;

    if(result&0b1)
        PF_flag++;
    if(result&0b10)
        PF_flag++;
    if(result&0b100)
        PF_flag++;
    if(result&0b1000)
        PF_flag++;
    if(result&0b10000)
        PF_flag++;
    if(result&0b100000)
        PF_flag++;
    if(result&0b1000000)
        PF_flag++;
    if(result&0b10000000)
        PF_flag++;
    if(PF_flag%2==0)
       cpu.PF=1;
    else cpu.PF=0;

    print_asm_template2();

}
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)


#include "cpu/exec/template-end.h"

