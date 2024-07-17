#include "print_ast.h"
#include <stdio.h>

// Function to print the AST list
void print_ast_list(ast_list_t *list, int depth) {
    while (list) {
        print_ast(list->elem, depth);
        list = list->next;
    }
}

// Function to print the AST node
void print_ast(ast_t *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    switch (node->type) {
        case AST_INTEGER:
            printf("AST_INTEGER: %ld\n", node->integer);
            break;
        case AST_VARIABLE:
            printf("AST_VARIABLE: %s (type %d)\n", node->var.name, node->var.type);
            break;
        case AST_BINARY:
            printf("AST_BINARY (op %d):\n", node->binary.op);
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case AST_UNARY:
            printf("AST_UNARY (op %d):\n", node->unary.op);
            print_ast(node->unary.operand, depth + 1);
            break;
        case AST_FUNCTION:
            printf("AST_FUNCTION: %s (return type %d)\n", node->function.name, node->function.return_type);
            printf("Params:\n");
            print_ast_list(node->function.params, depth + 1);
            printf("Statements:\n");
            print_ast_list(node->function.stmts, depth + 1);
            break;
        case AST_FNCALL:
            printf("AST_FNCALL: %s\n", node->call.name);
            print_ast_list(node->call.args, depth + 1);
            break;
        case AST_COMPOUND_STATEMENT:
            printf("AST_COMPOUND_STATEMENT:\n");
            print_ast_list(node->compound_stmt.stmts, depth + 1);
            break;
        case AST_CONDITION:
            printf("AST_CONDITION:\n");
            printf("Condition:\n");
            print_ast(node->condition.condition, depth + 1);
            printf("Then:\n");
            print_ast(node->condition.then, depth + 1);
            if (node->condition.Else) {
                printf("Else:\n");
                print_ast(node->condition.Else, depth + 1);
            }
            break;
        case AST_LOOP:
            printf("AST_LOOP:\n");
            printf("Condition:\n");
            print_ast(node->loop.condition, depth + 1);
            printf("Statement:\n");
            print_ast(node->loop.stmt, depth + 1);
            break;
        case AST_RETURN:
            printf("AST_RETURN:\n");
            print_ast(node->ret.expr, depth + 1);
            break;
        case AST_ASSIGNMENT:
            printf("AST_ASSIGNMENT:\n");
            print_ast(node->assignment.lvalue, depth + 1);
            print_ast(node->assignment.rvalue, depth + 1);
            break;
        default:
            printf("Unknown AST node type: %d\n", node->type);
            break;
    }
}
