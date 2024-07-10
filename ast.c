#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

ast_t *ast_new_unary(ast_unary_e op, ast_t *operand) {
    if (!operand) {
        fprintf(stderr, "Invalid operand\n");
        return NULL;
    }

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

ast_t *ast_new_binary(ast_binary_e op, ast_t *left, ast_t *right) {
    // Allocate memory for the new AST node
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the node
    node->type = AST_BINARY;
    node->binary.op = op;
    node->binary.left = left;
    node->binary.right = right;

    return node;
}

// Function to create a new variable AST node
ast_t *ast_new_variable(char *name, var_type_e type) {
    // Allocate memory for the new AST node
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the node type
    node->type = AST_VARIABLE;

    // Allocate and copy the variable name
    node->var.name = (char *)malloc(strlen(name) + 1);
    if (!node->var.name) {
        fprintf(stderr, "Memory allocation failed\n");
        free(node);
        exit(EXIT_FAILURE);
    }
    strcpy(node->var.name, name);

    // Set the variable type
    node->var.type = type;

    return node;
}

ast_t *ast_new_function(char *name, var_type_e return_type, ast_list_t *params, ast_list_t *stmts) {
    // Allocate memory for the new AST node
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the node
    node->type = AST_FUNCTION;
    node->function.name = strdup(name);
    if (!node->function.name) {
        fprintf(stderr, "Memory allocation failed\n");
        free(node);
        exit(EXIT_FAILURE);
    }
    node->function.return_type = return_type;
    node->function.params = params;
    node->function.stmts = stmts;

    return node;
}

ast_t *ast_new_fncall(char *name, ast_list_t *args) {
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = AST_FNCALL;
    node->call.name = strdup(name);
    if (!node->call.name) {
        fprintf(stderr, "Memory allocation failed\n");
        free(node);
        exit(EXIT_FAILURE);
    }
    node->call.args = args;
    return node;
}

ast_t *ast_new_comp_stmt(ast_list_t *stmts) {
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = AST_COMPOUND_STATEMENT;
    node->compound_stmt.stmts = stmts;
    return node;
}

ast_t *ast_new_integer(long val) {
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = AST_INTEGER;
    node->integer = val;
    return node;
}

ast_t *ast_new_assignment(ast_t *lvalue, ast_t *rvalue) {
    if (!lvalue || !rvalue) {
        fprintf(stderr, "Invalid lvalue or rvalue\n");
        return NULL;
    }

    // Allocate memory for the new AST node
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Initialize the node
    node->type = AST_ASSIGNMENT;
    node->assignment.lvalue = lvalue;
    node->assignment.rvalue = rvalue;

    return node;
}

ast_t *ast_new_loop(ast_t *condition, ast_t *stmt) {
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = AST_LOOP;
    node->loop.condition = condition;
    node->loop.stmt = stmt;
    return node;
}

ast_t *ast_new_return(ast_t *expr) {
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->type = AST_RETURN;
    node->ret.expr = expr;
    return node;
}

ast_t *ast_new_declaration(ast_t *lvalue, ast_t *rvalue) {
    if (!lvalue || !rvalue) {
        fprintf(stderr, "Invalid lvalue or rvalue\n");
        return NULL;
    }

    // Allocate memory for the new AST node
    ast_t *node = (ast_t *)malloc(sizeof(ast_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Initialize the node
    node->type = AST_DECLARATION;
    node->assignment.lvalue = lvalue;
    node->assignment.rvalue = rvalue;

    return node;
}

ast_list_t *ast_list_new_node(ast_t *elem) {
    ast_list_t *node = (ast_list_t *)malloc(sizeof(ast_list_t));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->elem = elem;
    node->next = NULL;
    return node;
}

ast_list_t *ast_list_add(ast_list_t **list, ast_t *elem) {
    ast_list_t *node = ast_list_new_node(elem);
    if (!*list) {
        *list = node;
    } else {
        ast_list_t *current = *list;
        while (current->next) {
            current = current->next;
        }
        current->next = node;
    }
    return node;
}
