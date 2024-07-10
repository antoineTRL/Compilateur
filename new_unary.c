#include "lexer.h"
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

void unary_example() {
    // Create a sample operand node
    ast_t *operand = (ast_t *)malloc(sizeof(ast_t));
    if (!operand) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    operand->type = AST_INTEGER;
    operand->integer = 10;

    // Create a unary node using the ast_new_unary function
    ast_t *unary_node = ast_new_unary(AST_UNARY_NEGATE, operand);
    if (unary_node) {
        printf("Unary node created with type: %d\n", unary_node->unary.op);
    }
}

void assignment_example() {
    // Create a sample lvalue node
    ast_t *lvalue = (ast_t *)malloc(sizeof(ast_t));
    if (!lvalue) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    lvalue->type = AST_VARIABLE;
    lvalue->var.name = strdup("x");
    lvalue->var.type = VAR_TYPE_INT;

    // Create a sample rvalue node
    ast_t *rvalue = (ast_t *)malloc(sizeof(ast_t));
    if (!rvalue) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    rvalue->type = AST_INTEGER;
    rvalue->integer = 42;

    // Create an assignment node using the ast_new_assignment function
    ast_t *assignment_node = ast_new_assignment(lvalue, rvalue);
    if (assignment_node) {
        printf("Assignment node created:\n");
        printf("Lvalue: %s\n", assignment_node->assignment.lvalue->var.name);
        printf("Rvalue: %ld\n", assignment_node->assignment.rvalue->integer);
    }

    // Free the allocated memory
    free(lvalue->var.name);
    free(lvalue);
    free(rvalue);
    free(assignment_node);
}
