%{
    #include "../lexer/lexeme_table.h"
    #include "../utils/hash.h"

    #include "parser.h"

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    int yylex();

    extern FILE *yyin;
    extern FILE *yyout;

    extern int error_line;
    extern char *yytext;

    int current_lexeme_code;
%}


%token PROG
%token SEMICOLON TWO_POINTS COMMA DOT_DOT OPEN_PARENTHESIS CLOSE_PARENTHESIS
%token START END
%token ARRAY OF OPEN_BRACKET CLOSE_BRACKET
%token IDENTIFIER VARIABLE OPAFF
%token STRUCT FSTRUCT
%token TYPE INTEGER FLOAT BOOLEAN CHARACTER STRING 
%token PROCEDURE FUNCTION RETURN_TYPE RETURN_VALUE
%token IF ELSE WHILE
%token EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL

%left AND OR 
%right NOT

%left PLUS MINUS
%left MULTIPLY DIVIDE
%%

program: PROG declaration_list statement_list
       | ;

// Conditions and boolean expressions
condition: OPEN_PARENTHESIS expression comparison_operator expression CLOSE_PARENTHESIS
         | OPEN_PARENTHESIS condition CLOSE_PARENTHESIS
         | condition AND condition
         | condition OR condition
         | NOT condition
         | NOT expression
         ;

loop: WHILE condition statement_block ;

comparison_operator: EQUAL
                   | NOT_EQUAL
                   | LESS_THAN
                   | GREATER_THAN
                   | LESS_EQUAL
                   | GREATER_EQUAL
                   ;

// Declarations
declaration_list: declaration_list declaration
                | ;

declaration: variable_declaration 
           | function_declaration 
           | type_declaration
           | procedure_declaration 
           ;

variable_declaration: VARIABLE IDENTIFIER TWO_POINTS type SEMICOLON 
                     ;

function_declaration: FUNCTION IDENTIFIER OPEN_PARENTHESIS parameter_list CLOSE_PARENTHESIS RETURN_TYPE type START declaration_list statement_list return_statement END ;

procedure_declaration: PROCEDURE IDENTIFIER OPEN_PARENTHESIS parameter_list CLOSE_PARENTHESIS START declaration_list statement_list END ;

type_declaration: TYPE IDENTIFIER TWO_POINTS STRUCT START complex_type_fields END FSTRUCT SEMICOLON
                | TYPE IDENTIFIER TWO_POINTS ARRAY dimension OF type_name SEMICOLON ;



argument_list: argument_list COMMA expression
    | expression
    | ;

parameter_list: parameter_list COMMA parameter
    | parameter
    | ;

parameter: IDENTIFIER TWO_POINTS type ;



dimension: OPEN_BRACKET list_dimensions CLOSE_BRACKET ;

list_dimensions: one_dimension
               | list_dimensions COMMA one_dimension ;

one_dimension: INTEGER DOT_DOT INTEGER ;

// Arithmetic expressions
expression: expression PLUS expression
          | expression MINUS expression
          | expression MULTIPLY expression
          | expression DIVIDE expression
          | expression_atom ;

expression_atom: function_call_expression  
               | IDENTIFIER
               | INTEGER
               | FLOAT
               | OPEN_PARENTHESIS expression CLOSE_PARENTHESIS ;

type: INTEGER
    | FLOAT
    | BOOLEAN
    | CHARACTER
    | STRING OPEN_BRACKET INTEGER CLOSE_BRACKET ;

complex_type_fields: type_field
                   | complex_type_fields type_field ;

type_field: IDENTIFIER TWO_POINTS type_name SEMICOLON ;

type_name: type
         | IDENTIFIER ;

function_call_expression: IDENTIFIER OPEN_PARENTHESIS argument_list CLOSE_PARENTHESIS ;

// Statements
statement_block: START statement_list END ;

statement_list: statement_list statement
              | ;

statement: assignment_statement
    | if_statement
    | standalone_function_call_statement
    | loop_statement ;

assignment_statement: IDENTIFIER OPAFF expression SEMICOLON 
                    ;

return_statement: RETURN_VALUE IDENTIFIER SEMICOLON;

if_statement: IF condition statement_block
            | IF condition statement_block ELSE statement_block;

loop_statement: loop;

standalone_function_call_statement: function_call_expression SEMICOLON ;



%%

static void print_usage(const char *program_name) {
    fprintf(stdout, COLOR_BOLD COLOR_UNDERLINE "\nUsage:" COLOR_RESET);
    fprintf(stdout, COLOR_GREEN " %s -f <file> [-v] [-h]\n" COLOR_RESET, program_name);

    fprintf(stdout, "\n");

    fprintf(stdout, COLOR_BOLD "Options:\n" COLOR_RESET);
    fprintf(stdout, "  " COLOR_YELLOW "-f <file>      " COLOR_RESET "The input file to be processed.\n");
    fprintf(stdout, "  " COLOR_YELLOW "-v             " COLOR_RESET "Enable verbose mode (display lexeme table).\n");
    fprintf(stdout, "  " COLOR_YELLOW "-h             " COLOR_RESET "Show help (this usage information).\n");

    fprintf(stdout, "\n");

    fprintf(stdout, COLOR_BOLD "Description:\n" COLOR_RESET);
    fprintf(stdout, "  This program compiles the specified input file.\n\n");

    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    int opt, verbose = 0;
    
    if (argc == 1) {
        // No arguments provided
        print_usage(argv[0]);
    }

    while ((opt = getopt(argc, argv, "f:vh")) != -1) {
        switch (opt) {
            case 'f':
                FILE *file = fopen(optarg, "r");
                if (!file) {
                    fprintf(stderr, COLOR_RED "Error: Could not open file %s\n" COLOR_RESET, optarg);
                    return 1;
                }
                
                yyin = file;
        
                init_hash_table();
                init_lexeme_table();
                
                yyparse();

                fclose(file);
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                print_usage(argv[0]);
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    if (verbose) {
        print_lexeme_table();
        print_hash_table();
    }

    return 0;
}
