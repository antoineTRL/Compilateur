#include "lexer.h"
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ast.h"

void unary_example() {
    // Create a sample operand node
    ast_t *operand = (ast_t *)malloc(sizeof(ast_t));
    if (!operand) {
        fprintf(stderr, "Memory allocation failed\n");
        //return EXIT_FAILURE;
    }
    operand->type = AST_INTEGER;
    operand->integer = 10;

    // Create a unary node using the ast_new_unary function
    ast_t *unary_node = ast_new_unary(AST_UNARY_NEGATE, operand);
    if (unary_node) {
        printf("Unary node created with type: %d\n", unary_node->type);
    }
}
