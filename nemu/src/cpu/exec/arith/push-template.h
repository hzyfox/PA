#include "cpu/exec/template-start.h"
#include "cpu/reg.h"
#define instr push

static void do_execute(){
print_asm_template1();

}

make_instr_helper(r);
#include "cpu/exec/template-end.h"

