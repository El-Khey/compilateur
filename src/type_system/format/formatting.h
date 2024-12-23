#ifndef __FORMAT_ARRAY_ACCESS_CODE_H__
#define __FORMAT_ARRAY_ACCESS_CODE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../ast/ast.h"
#include "../../symbol_table/declaration/declaration_table.h" 

char *format_struct_access(Node *struct_access);

char *format_array_access(Node *array_access);

char *format_expression(Node *expression);

char *format_func_proc_call(Node *func_proc_call);

#endif // __FORMAT_ARRAY_ACCESS_CODE_H__