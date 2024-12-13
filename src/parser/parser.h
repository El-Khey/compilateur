#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <string.h>

#include "../ast/ast.h"

#include "../../lib/colors.h"
#include "../utils/utils.h"

#include "../symbol_table/lexeme/lexeme_table.h"

#include "../symbol_table/declaration/declaration_table.h"
#include "../symbol_table/representation/representation_table.h"
#include "../symbol_table/hash/hash_table.h"

#include "../data/region_table.h"

typedef enum {
    COMPILATION,
    INTERPRETATION
} Mode;

void ylog(int log);

void ydebug(int debug);

int yyrun();


#endif // __PARSER_H__