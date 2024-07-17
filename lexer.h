#ifndef LEXER_H
#define LEXER_H

#include "buffer.h"

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_ASSIGN,
    TOKEN_SEMICOLON,
    TOKEN_LET,
    TOKEN_PRINT,
    TOKEN_END
} token_type_t;

typedef struct {
    token_type_t type;
    char *value;
} token_t;

token_t *lexer_get_token(buffer_t *buffer);

#endif // LEXER_H
