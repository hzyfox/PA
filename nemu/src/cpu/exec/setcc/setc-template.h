#include "cpu/exec/template-start.h"
#include "cpu/reg.h"
#define instr setc

static void do_execute(){
   if(cpu.CF==1){
    op_src->val=1;

    }else op_src->val=0;


print_asm_template1();

}



make_instr_helper(rm)
#include "cpu/exec/template-end.h"
