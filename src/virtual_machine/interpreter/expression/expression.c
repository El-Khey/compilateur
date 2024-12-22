#include "../../../symbol_table/lexeme/lexeme_table.h"

#include "../../../utils/utils.h"
#include "../../core/execution.h"

#include "expression.h"

vm_cell resolve_arithmetic_operation(int operation, vm_cell left, vm_cell right) {
    // First check for errors (div by 0)
    if (operation == A_DIV_OP && (right.type == INTEGER && right.value.integer == 0) ||
        (right.type == REAL && right.value.real == 0.0)) {
        set_error_type(&error, DIVISION_BY_ZERO);
        set_error_message(
            &error,
            "Division by zero error at %s.\n"
            "  Ensure the right operand is not zero for division operations.\n",
            get_formatted_location()
        );
     
        yerror(error);
        exit(EXIT_FAILURE);
    }

    // Then perform the operation
    switch (operation) {
        case A_ADD_OP:
            if (left.type == INTEGER && right.type == INTEGER) {
                int result = left.value.integer + right.value.integer;
                return construct_vm_cell(INTEGER, &result);
            }
            else if (left.type == REAL && right.type == REAL) {
                double result = left.value.real + right.value.real;
                return construct_vm_cell(REAL, &result);
            }
            break;

        case A_SUB_OP:
            if (left.type == INTEGER && right.type == INTEGER) {
                int result = left.value.integer - right.value.integer;
                return construct_vm_cell(INTEGER, &result);
            }
            else if (left.type == REAL && right.type == REAL) {
                double result = left.value.real - right.value.real;
                return construct_vm_cell(REAL, &result);
            }
            break;

        case A_MUL_OP:
            if (left.type == INTEGER && right.type == INTEGER) {
                int result = left.value.integer * right.value.integer;
                return construct_vm_cell(INTEGER, &result);
            }
            else if (left.type == REAL && right.type == REAL) {
                double result = left.value.real * right.value.real;
                return construct_vm_cell(REAL, &result);
            }
            break;

        case A_DIV_OP:
            if (left.type == INTEGER && right.type == INTEGER) {
                int result = left.value.integer / right.value.integer;
                return construct_vm_cell(INTEGER, &result);
            }
            else if (left.type == REAL && right.type == REAL) {
                double result = left.value.real / right.value.real;
                return construct_vm_cell(REAL, &result);
            }
            break;
    }
}
        

vm_cell resolve_expression(Node *expression) {
    if (expression == NULL) return construct_vm_cell(NULL_VALUE, NULL);

    switch (expression->type) {
        case A_IDENTIFIER: {
            vm_cell cell = get_variable_cell(expression->index_declaration);
            if (!cell.is_initialized) {
                set_error_type(&error, UNINITIALIZED_VARIABLE);
                set_error_message(
                    &error,
                    "Uninitialized variable '%s' at %s.\n"
                    "  Ensure the variable is initialized before use.\n",
                    get_lexeme(expression->index_lexicographic),
                    get_formatted_location()
                );
                yerror(error);
                exit(EXIT_FAILURE);
            }

            return cell;
        }

        case A_INTEGER_LITERAL: {
            int value = atoi(get_lexeme(expression->index_lexicographic));
            return construct_vm_cell(INTEGER, &value);
        }

        case A_FLOAT_LITERAL: {
            double value = atof(get_lexeme(expression->index_lexicographic));
            return construct_vm_cell(REAL, &value);
        }

        case A_BOOLEAN_LITERAL: {
            int value = (strcmp(get_lexeme(expression->index_lexicographic), "true") == 0) ? 1 : 0;
            return construct_vm_cell(BOOLEAN, &value);
        }

        case A_CHARACTER_LITERAL: {
            char *lexeme = get_lexeme(expression->index_lexicographic);
            char value = lexeme[1];
            return construct_vm_cell(CHARACTER, &value);
        }

        // TODO: string!

        case A_ADD_OP:
        case A_SUB_OP:
        case A_MUL_OP:
        case A_DIV_OP: {
            vm_cell left = resolve_expression(expression->child);
            vm_cell right = resolve_expression(expression->child->sibling);

            return resolve_arithmetic_operation(expression->type, left, right);
        }

        // case A_ARRAY_ACCESS:
        // case A_STRUCT_FIELD_ACCESS: 
        // case A_FUNC_PROC_CALL_STATEMENT: 
        default:
            printf("Expression type not yet implemented.\n");
            break;
    } 

    return construct_vm_cell(NULL_VALUE, NULL); // Return a default value for unhandled cases
}
