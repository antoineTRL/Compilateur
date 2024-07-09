#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

ast_t *ast_new_unary(ast_unary_e op, ast_t *operand) {
    // Allocate memory for the new AST node
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the node
    node->type = AST_UNARY;
    node->unary.op = op;
    node->unary.operand = operand;

    return node;
}
