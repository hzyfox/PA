#include "cpu/exec/template-start.h"
#include "cpu/reg.h"
#define instr call


static void do_execute(){
   int len=concat4(decode_, i, _, SUFFIX)(cpu.eip+1)+1;

    #if DATA_BYTE==2
   cpu.esp-=4;
   MEM_W(cpu.esp,cpu.eip+len);

   cpu.eip=(op_src->val+cpu.eip)&0x0000FFFF;

   #else
   cpu.esp-=4;
   MEM_W(cpu.esp,cpu.eip+len);

   cpu.eip+=op_src->val;
   #endif // DATA_BYTE

   print_asm_template1();


}

make_instr_helper(i)
make_helper(concat5(instr, _, rm, _, SUFFIX)){
int len=concat4(decode_, rm, _, SUFFIX)(cpu.eip+1)+1;
 #if DATA_BYTE==2
   cpu.esp-=4;
   MEM_W(cpu.esp,cpu.eip+len);

   cpu.eip=(op_src->val+cpu.eip)&0x0000FFFF;

   #else
   cpu.esp-=4;
   MEM_W(cpu.esp,cpu.eip+len);

   cpu.eip+=op_src->val;
   #endif // DATA_BYTE

   print_asm_template1();
   return len;



}
#include "cpu/exec/template-end.h"
