#ifndef PRINT_AST_H
#define PRINT_AST_H

#include "ast.h"

void print_ast(ast_t *node, int depth);
void print_ast_list(ast_list_t *list, int depth);

#endif // PRINT_AST_H
