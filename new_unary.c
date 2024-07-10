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

void binary_example(){
    // Create a sample left node
    ast_t *left = (ast_t *)malloc(sizeof(ast_t));
    if (!left) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    left->type = AST_INTEGER;
    left->integer = 10;

    // Create a sample right node
    ast_t *right = (ast_t *)malloc(sizeof(ast_t));
    if (!right) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    right->type = AST_INTEGER;
    right->integer = 20;

    // Create a binary node using the ast_new_binary function
    ast_t *binary_node = ast_new_binary(AST_BINARY_ADD, left, right);
    if (binary_node) {
        printf("Binary node created with type: %d\n", binary_node->binary.op);
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

void declaration_example() {
    // Create a sample lvalue node
    ast_t *lvalue = (ast_t *) malloc(sizeof(ast_t));
    if (!lvalue) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    lvalue->type = AST_VARIABLE;
    lvalue->var.name = strdup("x");
    lvalue->var.type = VAR_TYPE_INT;

    // Create a sample rvalue node
    ast_t *rvalue = (ast_t *) malloc(sizeof(ast_t));
    if (!rvalue) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    rvalue->type = AST_INTEGER;
    rvalue->integer = 42;

    // Create a declaration node using the ast_new_declaration function
    ast_t *declaration_node = ast_new_declaration(lvalue, rvalue);
    if (declaration_node) {
        printf("Declaration node created:\n");
        printf("Lvalue: %s\n", declaration_node->assignment.lvalue->var.name);
        printf("Rvalue: %ld\n", declaration_node->assignment.rvalue->integer);
    }
}