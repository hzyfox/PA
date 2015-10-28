#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <elf.h>

void cpu_exec(uint32_t);

WP* new_wp();
void free_wp(int num);
WP* get_head();

extern char *strtab ;
 extern Elf32_Sym *symtab;
 extern int nr_symtab_entry;


/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_p(char*args){
int num;
bool success;
num=expr(args,&success);
printf("%s=%x\n",args,num);
return 0;

}

static int cmd_si(char *args)
{
        int num;
	bool sucess;

    if(args==NULL)
    {
        cpu_exec(1);
    }
    else
    {
        num=expr(args,&sucess);

        if(num==0)
            printf("单步执行命令格式不合法\n");
        else{

            cpu_exec(num);
}
    }
return 0;
}

static int cmd_x(char *args){
    char*arg=strtok(NULL," ");
    int num=atoi(arg);
    int i;
    bool success;
    uint32_t adress;
    char*arg1=args+strlen(arg)+1;

    adress=expr(arg1,&success);
    for(i=0;i<num;i++){
        printf("%x\n",swaddr_read(adress+4*i,4));
    }
    return 0;

}
static int cmd_w(char*args)
{
   WP*temp;
   uint32_t addr;
   bool success;
   addr=expr(args,&success);//这里的adress的值需要用求值表达式来算
   temp=new_wp();

   strcpy(temp->adress,args);

   temp->value=addr;

    return 0;

}

static int cmd_info(char*args)
{
    char*arg=strtok(NULL," ");
    if(!strcmp("r",arg))//print reg
        printf("eax is %x\t ecx is %x\t \nedx is %x\t ebx is %x\t \nesp is %x\t ebp is %x\t \nesi is %x\t edi is %x\n",cpu.eax,cpu.ecx,cpu.edx,cpu.ebx,cpu.esp,cpu.ebp,
cpu.esi,cpu.edi);

    else if(!strcmp("w",arg))
    {
        WP *p;
        p=get_head();
        while(p!=NULL)
        {
            printf("NO is %d\t,adress is %s\t,value is %x\n",p->NO,p->adress,p->value);
            p=p->next;

        }

    }
    else
    {
        printf("未知命令%s",arg);
    }


    return 0;

}

static int cmd_d(char* args)
{
	int num;

    num=atoi(args);
    free_wp(num);
    return 0;

}

static int cmd_help(char *args);
static int cmd_bt();

static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	{ "si","让程序单步执行N条指令后暂停执行，当N没有给出时，缺省为一",cmd_si},
	{ "p","求出表达式expr的值",cmd_p},
	{ "x","求出表达式EXPR的值，将结果作为起始内存地址，并以16进制的形式输出连续的N个4字节",cmd_x},
        { "w","当表达式EXPR的值发生变化时，暂停程序的执行,设置监视点",cmd_w},
	{ "d","删除监视点，删除序号为N的监视点",cmd_d},
        { "info","打印寄存器状态，打印监视点信息",cmd_info},

       {"bt","打印栈帧链",cmd_bt}


	/* TODO: Add more commands */

};

static int cmd_bt(){

int i=nr_symtab_entry;
for(;i>0;i--){
    if(ELF32_ST_TYPE(symtab[i-1].st_info)==STT_FUNC){
        printf("函数名是： %s   函数地址是 %d，参数是%d\t %d\t,%d\t,%d\t %d\t\n",&strtab[symtab[i-1].st_name],symtab[i-1].st_value,
    swaddr_read(cpu.esp+8,4),swaddr_read(cpu.esp+12,4),swaddr_read(cpu.esp+16,4),swaddr_read(cpu.esp,4),swaddr_read(cpu.esp+4,4));



    }



}
if(i==0)
printf("stack is not exit\n");

return 0;

}

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}



void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
