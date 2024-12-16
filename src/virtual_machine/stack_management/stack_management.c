#include "../../utils/stack.h"

#include "stack_management.h"

static Stack execution_stack;

void init_execution_stack() {
    execution_stack = construct_stack();
}

void push_execution_stack(int type, void *value) {
    vm_cell cell = construct_vm_cell(type, NULL);
    push(&execution_stack, &cell, sizeof(vm_cell));
}

void fprintf_vm_stack(FILE *out) {
    print_stack(execution_stack, format_cell);
}