#ifndef PARSER_H
#define PARSER_H

#include "buffer.h"
#include "symbol_table.h"
#include "ast.h"
#include "lexer.h"

typedef struct {
    buffer_t *buffer;
    token_t *current_token;
    symbol_table_t *symbol_table;
} parser_t;

void parser_init(parser_t *parser, buffer_t *buffer);
void parser_advance(parser_t *parser);
ast_t *parse_expression(parser_t *parser);
ast_t *parse_statement(parser_t *parser);
ast_t *parse_program(parser_t *parser);

#endif // PARSER_H
