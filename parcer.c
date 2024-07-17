#include "parser.h"
#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void parser_init(parser_t *parser, buffer_t *buffer) {
    parser->buffer = buffer;
    parser->current_token = lexer_get_token(buffer); // Initialize the first token
    parser->symbol_table = symbol_table_init(); // Initialize the symbol table
}

void parser_advance(parser_t *parser) {
    free(parser->current_token);
    parser->current_token = lexer_get_token(parser->buffer);
}

// Parse a factor (numbers, variables, unary operations)
ast_t *parse_factor(parser_t *parser) {
    token_t *token = parser->current_token;

    if (token->type == TOKEN_NUMBER) {
        parser_advance(parser);
        return ast_new_integer(strtol(token->value, NULL, 10));
    } else if (token->type == TOKEN_IDENTIFIER) {
        symbol_table_entry_t *entry = symbol_table_lookup(parser->symbol_table, token->value);
        if (!entry) {
            fprintf(stderr, "Undeclared variable: %s\n", token->value);
            exit(EXIT_FAILURE);
        }
        parser_advance(parser);
        return ast_new_variable(token->value, entry->type);
    } else if (token->type == TOKEN_PLUS || token->type == TOKEN_MINUS) {
        token_type_t op = token->type;
        parser_advance(parser);
        ast_t *operand = parse_factor(parser);
        return ast_new_unary(op == TOKEN_PLUS ? AST_UNARY_INCREMENT : AST_UNARY_DECREMENT, operand);
    }

    fprintf(stderr, "Unexpected token: %s\n", token->value);
    exit(EXIT_FAILURE);
}

// Parse terms (multiplication and division)
ast_t *parse_term(parser_t *parser) {
    ast_t *node = parse_factor(parser);

    while (parser->current_token->type == TOKEN_STAR || parser->current_token->type == TOKEN_SLASH) {
        token_type_t op = parser->current_token->type;
        parser_advance(parser);
        ast_t *right = parse_factor(parser);
        node = ast_new_binary(op == TOKEN_STAR ? AST_BINARY_MULTIPLY : AST_BINARY_DIVIDE, node, right);
    }

    return node;
}

// Parse expressions (addition and subtraction)
ast_t *parse_expression(parser_t *parser) {
    ast_t *node = parse_term(parser);

    while (parser->current_token->type == TOKEN_PLUS || parser->current_token->type == TOKEN_MINUS) {
        token_type_t op = parser->current_token->type;
        parser_advance(parser);
        ast_t *right = parse_term(parser);
        node = ast_new_binary(op == TOKEN_PLUS ? AST_BINARY_ADD : AST_BINARY_SUBTRACT, node, right);
    }

    return node;
}

// Parse statements
ast_t *parse_statement(parser_t *parser) {
    if (parser->current_token->type == TOKEN_LET) {
        parser_advance(parser);

        if (parser->current_token->type != TOKEN_IDENTIFIER) {
            fprintf(stderr, "Expected variable name after 'let'\n");
            exit(EXIT_FAILURE);
        }

        char *var_name = strdup(parser->current_token->value);
        parser_advance(parser);

        if (parser->current_token->type != TOKEN_ASSIGN) {
            fprintf(stderr, "Expected '=' after variable name\n");
            exit(EXIT_FAILURE);
        }

        parser_advance(parser);
        ast_t *expr = parse_expression(parser);

        if (parser->current_token->type != TOKEN_SEMICOLON) {
            fprintf(stderr, "Expected ';' after expression\n");
            exit(EXIT_FAILURE);
        }

        parser_advance(parser);
        ast_t *var_node = ast_new_variable(var_name, VAR_TYPE_INT);
        symbol_table_add(parser->symbol_table, var_name, VAR_TYPE_INT); // Add to symbol table
        return ast_new_assignment(var_node, expr);
    } else if (parser->current_token->type == TOKEN_PRINT) {
        parser_advance(parser);
        ast_t *expr = parse_expression(parser);

        if (parser->current_token->type != TOKEN_SEMICOLON) {
            fprintf(stderr, "Expected ';' after expression\n");
            exit(EXIT_FAILURE);
        }

        parser_advance(parser);
        return ast_new_fncall("print", ast_list_new_node(expr));
    }

    fprintf(stderr, "Unexpected statement\n");
    exit(EXIT_FAILURE);
}

// Parse the entire program
ast_t *parse_program(parser_t *parser) {
    ast_list_t *stmts = NULL;

    while (parser->current_token->type != TOKEN_END) {
        ast_t *stmt = parse_statement(parser);
        ast_list_add(&stmts, stmt);
    }

    return ast_new_comp_stmt(stmts);
}
