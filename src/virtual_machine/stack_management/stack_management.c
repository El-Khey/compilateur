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

void allocate_execution_cells(int type, int size) {
    for (int i = 0; i < size; i++) {
        vm_cell cell = construct_vm_cell(type, NULL);
        push_execution_stack(type, &cell);
    }
}

void update_execution_cell(int index, void *value) {
    vm_cell cell = *(vm_cell *) get_stack_value(execution_stack, index);

    update_vm_cell(&cell, value);
    update_stack(&execution_stack, index, &cell, sizeof(vm_cell));
}

void fprintf_vm_stack(FILE *out) {
    print_stack(execution_stack, format_cell);
}