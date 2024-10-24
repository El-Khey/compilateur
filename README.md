# Folder Structure

```
/cpyrr_compiler_project
│
├── /src
│   ├── /lexer
│   │   ├── lexeme_table.c             # Lexicographical table (lexeme storage, hash table implementation)
│   │   ├── lexeme_table.h             # Header file for lexeme table definitions
│   │   ├── lexer.l                    # Lexical analysis (token generation and lexeme identification)
│   │
│   ├── /parser
│   │   ├── yacc_parser.y              # YACC grammar file
│   │   ├── parser.c                   # Parser implementation (calls lexing functions and constructs AST)
│   │   ├── parser.h                   # Header file for parser declarations
│   │
│   ├── /ast
│   │   ├── ast.c                      # Abstract syntax tree (AST) creation and manipulation
│   │   ├── ast.h                      # Header file for AST data structures and functions
│   │
│   ├── /symbol_table
│   │   ├── declaration_table.c        # Declaration table implementation (for types, variables, functions)
│   │   ├── declaration_table.h        # Header file for declaration table definitions
│   │   ├── type_representation.c      # Type representation table (structures, arrays, functions)
│   │   ├── type_representation.h      # Header file for type table
│   │
│   ├── /virtual_machine
│   │   ├── stack_management.c         # Stack memory management (handling dynamic/static chaining)
│   │   ├── stack_management.h         # Header file for stack management functions
│   │   ├── virtual_machine.c          # Virtual machine implementation (interprets AST)
│   │   ├── virtual_machine.h          # Header file for VM functions
│   │
│   ├── /data
│   │   ├── region_table.c             # Region table implementation (region size, nesting, AST pointers)
│   │   ├── region_table.h             # Header file for region table definitions
│   │
│   ├── /utils
│   │   ├── hash.c                     # Hashing utility for lexeme table
│   │   ├── hash.h                     # Header file for hashing functions
│   │   ├── errors.c                   # Error handling utilities
│   │   ├── errors.h                   # Header file for error handling
│   │
│   ├── /bin
│   │   ├── intermediate_text.c        # Functions for generating and saving intermediate code
│   │   ├── intermediate_text.h        # Header for intermediate code generation
│   │
│   └── main.c                         # Main entry point for the compiler
│
├── /include
│   ├── lexer.h                        # Common header files for all components
│   ├── parser.h
│   ├── ast.h
│   ├── virtual_machine.h
│   ├── declaration_table.h
│   ├── hash.h
│   ├── errors.h
│
├── /test
│   ├── test_lexer.c                   # Unit tests for lexer functionality
│   ├── test_parser.c                  # Unit tests for parser functionality
│   ├── test_virtual_machine.c         # Unit tests for VM functionality
│   ├── test_declaration_table.c       # Unit tests for declaration table
│   ├── Makefile                       # Makefile for building and running tests
│
├── Makefile                           # Main Makefile to build the project
├── README.md                          # Project documentation
└── intermediate_files/                # Folder to store intermediate representation files for later interpretation
```

### Key Components:

1. **`/lexer`**: This directory contains code for lexical analysis and lexeme management using a hash table.
2. **`/parser`**: This holds the YACC grammar file and parser implementation.
3. **`/ast`**: Implements the abstract syntax tree (AST) to represent the parsed program structure.
4. **`/symbol_table`**: Manages the declaration table and type representation (for variables, functions, structures).
5. **`/virtual_machine`**: Implements the virtual machine, which interprets the AST and manages the stack.
6. **`/data`**: Contains the region table for tracking program regions and their associated data.
7. **`/utils`**: Utility functions such as hashing and error handling.
8. **`/output`**: Handles saving the intermediate code/text needed for future interpretation.
9. **`/test`**: Unit tests for each major component of the project to ensure proper functionality.
