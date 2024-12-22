# CPYRR Compiler Project

This project is a compiler for the CPYRR programming language, which is a simple language designed for educational purposes. The compiler is implemented in C and uses the YACC parser generator to parse the language grammar. It generates an abstract syntax tree (AST) from the parsed program and interprets the AST using a virtual machine.

## Notes

- The project is still under development and is not yet complete.
- The project is structured into different components, each handling a specific part of the compilation process.
- A Makefile is provided to build the project and run the compiler.

## Folder Structure

```bash
/compiler
│
├── /example
│   ├── /compilation                 # Examples and test cases for the compilation process
│   │   ├── /errors                  # Compilation error examples
│   │   ├── /to-clean                # Samples to validate and clean compilation phases
│   │   ├── /todo                    # Examples of incomplete or pending tasks
│   ├── /interpretation              # Examples for the interpretation process
│
├── /lib                             # Common libraries
│   ├── colors.h                     # Color utilities for terminal output
│   ├── table_printer.h              # Utilities for table printing
│
├── /report                          # Archive of development logs and templates
│   ├── Archive*.txt                 # Archived logs for project development
│   ├── template.txt                 # Template file for report creation
│
├── /src
│   ├── /ast
│   │   ├── ast.c                    # Abstract syntax tree (AST) creation and manipulation
│   │   ├── ast.h                    # Header file for AST data structures and functions
│   │   ├── lcrs.c                   # Left-Child Right-Sibling (LCRS) tree implementation
│   │   ├── lcrs.h                   # Header file for LCRS tree functions
│   │   ├── node_type.h              # Header file for defining AST node types
│   │
│   ├── /bin
│   │   ├── lex.yy.c                 # Generated lexical analyzer (by flex)
│   │   ├── y.tab.c                  # Generated parser (by yacc)
│   │   ├── y.tab.h                  # Header file for parser definitions
│   │
│   ├── /data
│   │   ├── region_stack.c           # Region stack management
│   │   ├── region_stack.h           # Header file for region stack functions
│   │   ├── region_table.c           # Region table implementation (region size, nesting, AST pointers)
│   │   ├── region_table.h           # Header file for region table definitions
│   │
│   ├── /lexer
│   │   ├── interpreter_lexer.l      # Lexical analyzer for the interpreter
│   │   ├── lexer.l                  # Lexical analysis (token generation and lexeme identification)
│   │
│   ├── /parser
│   │   ├── grammar.y                # YACC grammar file
│   │   ├── interpreter_grammar.y    # Grammar file for interpretation phase
│   │   ├── parser.c                 # Parser implementation (calls lexing functions and constructs AST)
│   │   ├── parser.h                 # Header file for parser declarations
│   │
│   ├── /semantic_analysis           # Semantic analysis and validation phase
│   │   ├── /assignment_checks       # Assignment validation utilities
│   │   ├── /condition_checks        # Condition validation utilities
│   │   ├── /function_checks         # Function and procedure validation utilities
│   │   ├── /scope_checks            # Scope validation utilities
│   │   ├── /type_checks             # Type validation utilities
│   │   ├── /variable_checks         # Variable validation utilities
│   │   ├── validation_utils.h       # Common utilities for semantic checks
│   │   ├── semantic_checks.h        # Aggregator header for semantic checks
│   │
│   ├── /symbol_table
│   │   ├── declaration              # Declaration table management
│   │   ├── hash                     # Hash table utilities for symbol storage
│   │   ├── lexeme                   # Lexeme table management
│   │   ├── representation           # Type and structure representation table
│   │   ├── utility.c                # Common utilities for symbol table
│   │   ├── utility.h                # Header file for common utilities
│   │
│   ├── /table_management
│   │   ├── array_manager.c          # Array-specific management utilities
│   │   ├── func_proc_manager.c      # Function and procedure management utilities
│   │   ├── structure_manager.c      # Structure-specific utilities
│   │   ├── variable_manager.c       # Variable-specific utilities
│   │
│   ├── /type_system
│   │   ├── /format                  # Format utilities for messages and output
│   │   ├── /type_inference          # Type inference for expressions and structures
│   │
│   └── /utils
│       ├── errors.c                 # Error handling utilities
│       ├── scope_tracker.c          # Scope tracking utilities
│       ├── stack.c                  # Stack utilities
│       ├── utils.h                  # General utility macros and functions
│   
│
├── /tests
│   ├── regression                   # Regression tests for validating components
│
├── Makefile                         # Main Makefile to build the project
├── README.md                        # Project documentation
└── requirements.txt                 # Project dependencies
```

## Key Components

1. **`/example`**: Test cases and example programs for both compilation and interpretation phases.
2. **`/lib`**: Helper libraries for enhanced output and table visualization.
3. **`/src`**: Core implementation files, including lexer, parser, semantic analysis, AST, and symbol table.
4. **`/tests`**: Regression tests to ensure the correctness of implemented features.
5. **Makefile**: Build and automation for the compiler and virtual machine.

---

## Error Messages

- **Title Line**: Error details with a reference to the source code line.
- **Context**: Highlights the issue and its surrounding code snippet.
- **Advice**: Provides suggestions or steps to resolve the error.

## AST Node Format in Intermediate Code

```text
Node(<type>, <lex-index>, <decl-index>) [Child: <child>] [Sibling: <sibling>]
```

This format ensures consistency when interpreting or debugging the AST representation.

---

## Virtual Machine

Pour affecter correctement une valeur à un tableau dans votre pile d'exécution, vous devez calculer l'adresse exacte de l'emplacement où la valeur doit être stockée. Cette adresse est déterminée par les indices donnés lors de l'accès au tableau et les informations de dimensionnalité (comme les bornes des dimensions) dans la table des déclarations et la table de représentation. Voici comment procéder :

---

### **Mathematical Formulas**

#### **2. Calculer l'adresse dans la pile d'exécution**

Le calcul de l'adresse repose sur la formule suivante pour les tableaux multidimensionnels :

\[
\text{adresse} = \text{base} + \sum_{i=1}^n (\text{indice}_i - \text{borne inférieure}_i) \times \prod_{j=i+1}^n (\text{borne supérieure}_j - \text{borne inférieure}_j + 1)
\]

Où :

- \( \text{base} \) est l'adresse de départ du tableau dans la pile d'exécution.
- \( \text{indice}_i \) est la valeur donnée pour la \( i^{\text{ème}} \) dimension.
- \( \text{borne inférieure}_i \) et \( \text{borne supérieure}_i \) sont respectivement les bornes inférieure et supérieure de la \( i^{\text{ème}} \) dimension.
- \( n \) est le nombre de dimensions.

---

To compute the address of a specific field in a structure, we use the following mathematical formulas based on the **base address** of the structure, the **offset** of the field within the structure, and the **displacement in memory**.

---

#### **1. General Formula for the Address of a Field**

\[
\text{Address of Field} = \text{Base Address of Structure} + \text{Field Offset}
\]

- **Base Address of Structure**: The starting address in memory where the structure is allocated (retrieved from the declaration table).
- **Field Offset**: The relative position (in bytes or memory cells) of the field from the beginning of the structure, as defined in the representation table.

---

#### **2. Calculating the Field Offset**

Each field in a structure has a **displacement** or **offset**, which is calculated as the sum of the sizes of all preceding fields. For a field \( f_k \), its offset is given by:
\[
\text{Field Offset of } f_k = \sum_{i=1}^{k-1} \text{Size of Field } f_i
\]

Where:

- \( k \): The position of the field in the structure.
- \( \text{Size of Field } f_i \): The size (in memory units) of the \( i^\text{th} \) field, retrieved from the declaration or type information.

---

#### **3. Memory Size for Each Field**

For **basic types** (e.g., integers, booleans, characters), the size is typically predefined by the virtual machine, in our case each base type has a size of 1.

For **complex types** (e.g., arrays, structures), the size depends on their specific declaration:

- **Array**: Calculated as:
\[
\text{Size of Array} = \prod_{i=1}^{n} (\text{Upper Bound}_i - \text{Lower Bound}_i + 1) \times \text{Element Size}
\]

- **Nested Structures**: Use the same formula recursively.

---

### **Step-by-Step Breakdown**

For a structure with \( N \) fields:

1. **Identify the Base Address**:
   \[
   \text{Base Address of Structure} = \text{Execution Address from Declaration Table}
   \]

2. **Locate the Field Description**:
   For a field \( f_k \), find its **displacement** (\( d_k \)) in the Representation Table.

3. **Final Address Calculation**:
   \[
   \text{Address of Field } f_k = \text{Base Address of Structure} + d_k
   \]

---

### **Generalization for Nested Structures**

If a field is itself a structure, its offset is added to the base address of the parent structure, and the offsets within the nested structure are calculated recursively.

For nested structures:
\[
\text{Address of Nested Field } f_{i,j} = \text{Base Address of Parent Structure} + \text{Offset of Field } f_i + \text{Offset of Subfield } f_j
\]

Master, this approach ensures clarity and precision for all scenarios involving structure-based memory computations.