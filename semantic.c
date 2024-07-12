#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"
#include "symbol_table.h"

void check_binary_expr(ast_t *node, symbol_table_t *table) {
    check_type(node->binary.left, table);
    check_type(node->binary.right, table);

    if (node->binary.left->var_type != node->binary.right->var_type) {
        fprintf(stderr, "Type error: incompatible types in binary expression\n");
        exit(EXIT_FAILURE);
    }
    node->var_type = node->binary.left->var_type;
}

void check_type(ast_t *node, symbol_table_t *table) {
    if (!node) return;

    switch (node->type) {
        case AST_INTEGER:
            node->var_type = VAR_TYPE_INT;
            break;
        case AST_VARIABLE: {
            symbol_table_entry_t *entry = symbol_table_lookup(table, node->var.name);
            if (!entry) {
                fprintf(stderr, "Undeclared variable: %s\n", node->var.name);
                exit(EXIT_FAILURE);
            }
            node->var_type = entry->type;
            break;
        }
        case AST_BINARY:
            check_binary_expr(node, table);
            break;
        case AST_UNARY:
            check_type(node->unary.operand, table);
            node->var_type = node->unary.operand->var_type;
            break;
        case AST_FNCALL:
            // Add function call type check
            break;
        case AST_FUNCTION:
            // Add function definition type check
            break;
        case AST_COMPOUND_STATEMENT:
            for (ast_list_t *stmt = node->compound_stmt.stmts; stmt; stmt = stmt->next) {
                check_type(stmt->elem, table);
            }
            break;
        case AST_CONDITION:
            check_type(node->condition.condition, table);
            check_type(node->condition.then, table);
            if (node->condition.Else) {
                check_type(node->condition.Else, table);
            }
            break;
        case AST_LOOP:
            check_type(node->loop.condition, table);
            check_type(node->loop.stmt, table);
            break;
        case AST_RETURN:
            check_type(node->ret.expr, table);
            break;
        default:
            fprintf(stderr, "Unknown AST node type: %d\n", node->type);
            exit(EXIT_FAILURE);
    }
}

int semantic_analysis(ast_t *node, symbol_table_t *table) {
    check_type(node, table);
    return 1; // Return 1 if semantic analysis passes
}
