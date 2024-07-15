#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symbol_table.h"

void check_type(ast_t *node, symbol_table_t *table);
void check_binary_expr(ast_t *node, symbol_table_t *table);

int semantic_analysis(ast_t *node, symbol_table_t *table);

#endif // SEMANTIC_H
