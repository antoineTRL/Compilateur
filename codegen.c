#include "codegen.h"
#include <stdio.h>
#include <string.h>

void generate_code(ast_t *node) {
    if (!node) return;

    switch (node->type) {
        case AST_ASSIGNMENT:
            printf("%s = ", node->assignment.lvalue->var.name);
        generate_code(node->assignment.rvalue);
        printf(";\n");
        break;
        case AST_FNCALL:
            if (strcmp(node->call.name, "print") == 0) {
                printf("print(");
                generate_code(node->call.args->elem); // Assuming print has a single argument
                printf(");\n");
            }
        break;
        case AST_INTEGER:
            printf("%ld", node->integer);
        break;
        case AST_VARIABLE:
            printf("%s", node->var.name);
        break;
        case AST_BINARY:
            printf("(");
        generate_code(node->binary.left);
        switch (node->binary.op) {
            case AST_BINARY_ADD: printf(" + "); break;
            case AST_BINARY_SUBTRACT: printf(" - "); break;
            case AST_BINARY_MULTIPLY: printf(" * "); break;
            case AST_BINARY_DIVIDE: printf(" / "); break;
            default: break;
        }
        generate_code(node->binary.right);
        printf(")");
        break;
        case AST_COMPOUND_STATEMENT:
            for (ast_list_t *stmt = node->compound_stmt.stmts; stmt; stmt = stmt->next) {
                generate_code(stmt->elem);
            }
        break;
        default:
            printf("Unknown AST node type: %d\n", node->type);
        break;
    }
}
