#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"



typedef struct watchpoint {
	int NO;
	char*adress;//要监视的expression
	int value;

	struct watchpoint *next;
	/* TODO: Add more members if necessary */


} WP;

#endif
