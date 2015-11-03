#include "cpu/exec/template-start.h"
#include "cpu/reg.h"
#define instr call
#include "monitor/monitor.h"
extern int str_len_flag;

static void do_execute(){
   Log("the str_len is %d",str_len_flag);

    #if DATA_BYTE==2
   cpu.esp-=4;
   MEM_W(cpu.esp,cpu.eip+str_len_flag);

   cpu.eip=(op_src->val+cpu.eip)&0x0000FFFF;

   #else
   cpu.esp-=4;
   MEM_W(cpu.esp,cpu.eip+str_len_flag);

   cpu.eip+=op_src->val;
   #endif // DATA_BYTE

   print_asm_template1();


}

make_instr_helper(i)
make_instr_helper(rm)
#include "cpu/exec/template-end.h"
