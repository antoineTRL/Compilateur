#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include "symbol_table.h"

typedef struct {
    buffer_t *buffer;
    char *current_token;
    symbol_table_t *symbol_table;
} parser_t;

void parser_init(parser_t *parser, buffer_t *buffer);
ast_t *parse_expression(parser_t *parser);
ast_t *parse_variable(parser_t *parser);
ast_t *parse_function(parser_t *parser);
ast_t *parse_statement(parser_t *parser);
ast_t *parse_program(parser_t *parser);

#endif // PARSER_H
