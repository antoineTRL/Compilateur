#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"

typedef struct {
    char *code;
    size_t size;
    size_t capacity;
} codegen_context_t;

void codegen_init(codegen_context_t *context);
void codegen_free(codegen_context_t *context);
void generate_code(ast_t *node, codegen_context_t *context);

#endif // CODEGEN_H
