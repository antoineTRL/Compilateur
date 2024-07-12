#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void parser_init(parser_t *parser, buffer_t *buffer) {
    parser->buffer = buffer;
    parser->current_token = lexer_getalphanum(buffer);
    parser->symbol_table = NULL; // Initialize to NULL or assign as needed
}

void parser_advance(parser_t *parser) {
    free(parser->current_token);
    parser->current_token = lexer_getalphanum(parser->buffer);
}

ast_t *parse_expression(parser_t *parser) {
    if (isdigit(parser->current_token[0])) {
        long value = strtol(parser->current_token, NULL, 10);
        parser_advance(parser);
        return ast_new_integer(value);
    } else if (isalpha(parser->current_token[0])) {
        char *name = strdup(parser->current_token);
        parser_advance(parser);
        return ast_new_variable(name, VAR_TYPE_INT);
    }
    return NULL; // Error handling needed
}

ast_t *parse_variable(parser_t *parser) {
    if (isalpha(parser->current_token[0])) {
        char *name = strdup(parser->current_token);
        parser_advance(parser);
        return ast_new_variable(name, VAR_TYPE_INT);
    }
    return NULL; // Error handling needed
}

ast_t *parse_function(parser_t *parser) {
    if (isalpha(parser->current_token[0])) {
        char *name = strdup(parser->current_token);
        parser_advance(parser);

        // Expect parameters and function body (simplified)
        ast_list_t *params = NULL; // Assuming params parsing implemented
        ast_list_t *stmts = NULL;  // Assuming stmts parsing implemented

        return ast_new_function(name, VAR_TYPE_INT, params, stmts);
    }
    return NULL; // Error handling needed
}

ast_t *parse_statement(parser_t *parser) {
    // This will be expanded with more statement types
    return parse_expression(parser);
}

ast_t *parse_program(parser_t *parser) {
    ast_list_t *stmts = NULL;
    while (parser->current_token != NULL) {
        ast_t *stmt = parse_statement(parser);
        if (stmt != NULL) {
            ast_list_add(&stmts, stmt);
        }
        parser_advance(parser);
    }
    return ast_new_comp_stmt(stmts);
}
