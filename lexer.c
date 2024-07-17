#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

token_t *lexer_get_token(buffer_t *buffer) {
    char *value = malloc(100);
    int index = 0;
    char ch = buf_getchar(buffer);

    // Skip whitespace
    while (isspace(ch)) {
        ch = buf_getchar(buffer);
    }

    // Recognize numbers
    if (isdigit(ch)) {
        do {
            value[index++] = ch;
            ch = buf_getchar(buffer);
        } while (isdigit(ch));
        // S'assurer que le buffer est verrouillé avant de faire un rollback
        if (!buffer->islocked) {
            buf_lock(buffer);
            buf_rollback(buffer, 1);
            buf_unlock(buffer);
        } else {
            buf_rollback(buffer, 1);
        }
        value[index] = '\0';

        token_t *token = malloc(sizeof(token_t));
        token->type = TOKEN_NUMBER;
        token->value = value;
        return token;
    }

    // Recognize identifiers and keywords
    if (isalpha(ch)) {
        do {
            value[index++] = ch;
            ch = buf_getchar(buffer);
        } while (isalnum(ch));
        // S'assurer que le buffer est verrouillé avant de faire un rollback
        if (!buffer->islocked) {
            buf_lock(buffer);
            buf_rollback(buffer, 1);
            buf_unlock(buffer);
        } else {
            buf_rollback(buffer, 1);
        }
        value[index] = '\0';

        token_t *token = malloc(sizeof(token_t));
        if (strcmp(value, "let") == 0) {
            token->type = TOKEN_LET;
        } else if (strcmp(value, "print") == 0) {
            token->type = TOKEN_PRINT;
        } else {
            token->type = TOKEN_IDENTIFIER;
        }
        token->value = value;
        return token;
    }

    // Recognize operators and delimiters
    token_t *token = malloc(sizeof(token_t));
    switch (ch) {
        case '+': token->type = TOKEN_PLUS; break;
        case '-': token->type = TOKEN_MINUS; break;
        case '*': token->type = TOKEN_STAR; break;
        case '/': token->type = TOKEN_SLASH; break;
        case '=': token->type = TOKEN_ASSIGN; break;
        case ';': token->type = TOKEN_SEMICOLON; break;
        case '\0': token->type = TOKEN_END; break;
        default:
            free(value);
        free(token);
        return NULL; // Unrecognized character
    }
    token->value = NULL;
    return token;
}
