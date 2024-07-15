#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

void codegen_init(codegen_context_t *context) {
    context->size = 0;
    context->capacity = 1024;
    context->code = malloc(context->capacity);
    context->code[0] = '\0';
}

void codegen_free(codegen_context_t *context) {
    free(context->code);
}

void append_code(codegen_context_t *context, const char *code) {
    size_t new_size = context->size + strlen(code);
    if (new_size >= context->capacity) {
        context->capacity *= 2;
        context->code = realloc(context->code, context->capacity);
    }
    strcat(context->code, code);
    context->size = new_size;
}

void generate_code(ast_t *node, codegen_context_t *context) {
    if (!node) return;

    switch (node->type) {
        case AST_INTEGER:
            {
                char buffer[32];
                sprintf(buffer, "PUSH %ld\n", node->integer);
                append_code(context, buffer);
            }
            break;
        case AST_VARIABLE:
            {
                char buffer[64];
                sprintf(buffer, "LOAD %s\n", node->var.name);
                append_code(context, buffer);
            }
            break;
        case AST_BINARY:
            generate_code(node->binary.left, context);
            generate_code(node->binary.right, context);
            switch (node->binary.op) {
                case AST_BINARY_ADD:
                    append_code(context, "ADD\n");
                    break;
                case AST_BINARY_SUBTRACT:
                    append_code(context, "SUB\n");
                    break;
                case AST_BINARY_MULTIPLY:
                    append_code(context, "MUL\n");
                    break;
                case AST_BINARY_DIVIDE:
                    append_code(context, "DIV\n");
                    break;
                default:
                    append_code(context, "UNKNOWN_OP\n");
                    break;
            }
            break;
        case AST_UNARY:
            generate_code(node->unary.operand, context);
            switch (node->unary.op) {
                case AST_UNARY_NEGATE:
                    append_code(context, "NEG\n");
                    break;
                default:
                    append_code(context, "UNKNOWN_UNARY_OP\n");
                    break;
            }
            break;
        case AST_FUNCTION:
            append_code(context, "FUNC_START\n");
            generate_code(node->function.stmts->elem, context); // Simplified for single statement
            append_code(context, "FUNC_END\n");
            break;
        case AST_FNCALL:
            append_code(context, "CALL ");
            append_code(context, node->call.name);
            append_code(context, "\n");
            break;
        case AST_COMPOUND_STATEMENT:
            for (ast_list_t *stmt = node->compound_stmt.stmts; stmt != NULL; stmt = stmt->next) {
                generate_code(stmt->elem, context);
            }
            break;
        case AST_RETURN:
            generate_code(node->ret.expr, context);
            append_code(context, "RETURN\n");
            break;
        default:
            append_code(context, "UNKNOWN_NODE_TYPE\n");
            break;
    }
}
