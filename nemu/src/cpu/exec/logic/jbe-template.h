#include "cpu/exec/template-start.h"
#include "cpu/reg.h"
#define instr jbe

static void do_execute(){
   if(cpu.CF==1||cpu.ZF==1){
    /*#if DATA_BYTE==1
        uint8_t val= (uint8_t)(cpu.eip&0xFF);
        val+=(uint8_t)op_src->val;
        cpu.eip=(cpu.eip&0xFFFFFF00)+val;
    #elif   DATA_BYTE==2
        uint16_t val= (uint16_t)(cpu.eip&0xFFFF);
        val+=(uint16_t)op_src->val;
        cpu.eip=(cpu.eip&0xFFFF0000)+val;
    #else

        cpu.eip=cpu.eip+op_src->val;
    #endif // DATA_BYTE
    */
    #if DATA_BYTE==1
    cpu.eip+=(DATA_TYPE_S)op_src->val;
    #elif DATA_BYTE==2
    cpu.eip=cpu.eip+(DATA_TYPE_S)op_src->val;
    cpu.eip=cpu.eip&0xFFFF;
    #else
    cpu.eip+=(int32_t)op_src->val;
    #endif // DATA_BYTE

    }



print_asm_template1();


 /*#if DATA_BYTE==1
    cpu.eip=cpu.eip+(int_8)op_src->val
    #elif DATA_BYTE==2
    cpu.eip=(cpu.eip+(int16_t)op_src->val)&0xFFFF;
    #else
    cpu.eip=cpu.eip+(int32_t)op_src->val;
    #endif // DATA_BYTE
    */






}



make_instr_helper(i)
#include "cpu/exec/template-end.h"
