#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "setpo-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "setpo-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "setpo-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */

make_helper_v(setpo_rm)
