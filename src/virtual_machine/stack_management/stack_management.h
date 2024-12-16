#ifndef __STACK_MANAGEMENT_H__
#define __STACK_MANAGEMENT_H__

#include "../core/vm_cell.h"

void init_execution_stack();

void push_execution_stack(int type, void *value);

void fprintf_vm_stack(FILE *out);

#endif 
