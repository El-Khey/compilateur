#include "../symbol_table/declaration_table.h" 
#include "../lexer/lexeme_table.h"
#include "../data/region_table.h"
#include "scope_tracker.h"
#include "validation.h"


void check_base_type(int index_lexeme_lexicographic) {
       if(!is_declaration_base_type(index_lexeme_lexicographic)) {
        set_error_type(&error, TYPE_ERROR);
        set_error_message(&error, "Type '%s' should be a base type (int, float, bool, char).", get_lexeme(index_lexeme_lexicographic));

        yerror(error);
    }   
}

void check_variable_definition(int index_lexeme_lexicographic) {
    if (find_declaration_index(index_lexeme_lexicographic) == NULL_VALUE) {
        set_error_type(&error, SEMANTIC_ERROR);
        set_error_message(&error, "Variable '%s' is not defined.", get_lexeme(index_lexeme_lexicographic));

        yerror(error);
    }
}

void check_type_definition(int index_type_lexicographic) {
    if (find_declaration_index(index_type_lexicographic) == NULL_VALUE) {
        set_error_type(&error, TYPE_ERROR);
        set_error_message(&error, "Type '%s' is not defined.", get_lexeme(index_type_lexicographic));

        yerror(error);
    }
}

void check_func_proc_definition(int index_lexeme_lexicographic) {
    // TODO: the procedure call should not be assigned to a variable
    if (find_declaration_index_by_nature(index_lexeme_lexicographic, TYPE_FUNC) == NULL_VALUE && 
        find_declaration_index_by_nature(index_lexeme_lexicographic, TYPE_PROC) == NULL_VALUE) {

        set_error_type(&error, SEMANTIC_ERROR);
        set_error_message(&error, "Function or procedure '%s' is not defined.", get_lexeme(index_lexeme_lexicographic));

        yerror(error);
    }
}

void check_variable_redefinition(int index_lexeme_lexicographic) {
    int index_lexeme_declaration = find_declaration_index(index_lexeme_lexicographic);
    if (index_lexeme_declaration != NULL_VALUE) {
        set_error_type(&error, SEMANTIC_ERROR);
        set_error_message(&error, "Redefinition of variable '%s'.", get_lexeme(index_lexeme_lexicographic));
        
        int declaration_region = get_declaration_region(index_lexeme_declaration);
        int current_region = get_current_region_id();

        declaration_region == current_region ? yerror(error) : yywarn(error);
    }
}

void check_type_redefinition(int index_lexeme_lexicographic) {
    int index_lexeme_declaration = find_declaration_index(index_lexeme_lexicographic);
    if (index_lexeme_declaration != NULL_VALUE) {
        set_error_type(&error, TYPE_ERROR);
        set_error_message(&error, "Redefinition of type '%s'.", get_lexeme(index_lexeme_lexicographic));

        int declaration_region = get_declaration_region(index_lexeme_declaration);
        int current_region = get_current_region_id();

        declaration_region == current_region ? yerror(error) : yywarn(error);
    }
}

void check_func_proc_redefinition(int index_lexeme_lexicographic, char *type) {
    // TODO: Change condition to 'OR' if we don't want to allow function and procedure with the same name 
    if (find_declaration_index_by_nature(index_lexeme_lexicographic, TYPE_FUNC) != NULL_VALUE &&
        find_declaration_index_by_nature(index_lexeme_lexicographic, TYPE_PROC) != NULL_VALUE) {
        set_error_type(&error, SEMANTIC_ERROR);
        set_error_message(&error, "Redefinition of %s '%s'.", type, get_lexeme(index_lexeme_lexicographic));

        yerror(error);
    }
}

void check_scope_redefinition(int index_lexeme_lexicographic, char *entity_type) {
    if (is_identifier_already_tracked(index_lexeme_lexicographic)) {
        set_error_type(&error, SEMANTIC_ERROR);
        set_error_message(&error, "Identifier '%s' is already defined in the current scope as a %s.", get_lexeme(index_lexeme_lexicographic), entity_type);

        yerror(error);
    }
}
