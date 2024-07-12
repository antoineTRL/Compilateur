#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "lexer.h"
#include "ast.h"
#include "symbol_table.h"
#include "parser.h"
#include "semantic.h"

// Function declarations for testing
void unary_example();
void assignment_example();
void declaration_example();
void binary_example();
void print_ast(ast_t *node, int depth);
void print_ast_list(ast_list_t *list, int depth);

// Function to print the AST node
void print_ast(ast_t *node, int depth) {
    if (!node) return;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    switch (node->type) {
        case AST_VOID:
            printf("AST_VOID\n");
            break;
        case AST_INTEGER:
            printf("AST_INTEGER: %ld\n", node->integer);
            break;
        case AST_VARIABLE:
            printf("AST_VARIABLE: %s (type %d)\n", node->var.name, node->var.type);
            break;
        case AST_BINARY:
            printf("AST_BINARY (op %d):\n", node->binary.op);
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case AST_UNARY:
            printf("AST_UNARY (op %d):\n", node->unary.op);
            print_ast(node->unary.operand, depth + 1);
            break;
        case AST_FUNCTION:
            printf("AST_FUNCTION: %s (return type %d)\n", node->function.name, node->function.return_type);
            printf("Params:\n");
            print_ast_list(node->function.params, depth + 1);
            printf("Statements:\n");
            print_ast_list(node->function.stmts, depth + 1);
            break;
        case AST_FNCALL:
            printf("AST_FNCALL: %s\n", node->call.name);
            print_ast_list(node->call.args, depth + 1);
            break;
        case AST_COMPOUND_STATEMENT:
            printf("AST_COMPOUND_STATEMENT:\n");
            print_ast_list(node->compound_stmt.stmts, depth + 1);
            break;
        case AST_CONDITION:
            printf("AST_CONDITION:\n");
            printf("Condition:\n");
            print_ast(node->condition.condition, depth + 1);
            printf("Then:\n");
            print_ast(node->condition.then, depth + 1);
            if (node->condition.Else) {
                printf("Else:\n");
                print_ast(node->condition.Else, depth + 1);
            }
            break;
        case AST_LOOP:
            printf("AST_LOOP:\n");
            printf("Condition:\n");
            print_ast(node->loop.condition, depth + 1);
            printf("Statement:\n");
            print_ast(node->loop.stmt, depth + 1);
            break;
        case AST_RETURN:
            printf("AST_RETURN:\n");
            print_ast(node->ret.expr, depth + 1);
            break;
        default:
            printf("Unknown AST node type: %d\n", node->type);
            break;
    }
}

// Function to print the AST list
void print_ast_list(ast_list_t *list, int depth) {
    while (list) {
        print_ast(list->elem, depth);
        list = list->next;
    }
}

int main() {
    buffer_t buffer;
    FILE *file = fopen("example.txt", "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return EXIT_FAILURE;
    }

    buf_init(&buffer, file); // Ensure buffer is initialized
    symbol_table_t *table = symbol_table_init();

    char *alphanum;
    do {
        alphanum = lexer_getalphanum(&buffer);
        if (alphanum) {
            printf("Séquence alphanumérique trouvée : %s\n", alphanum);
            symbol_table_add(table, alphanum, VAR_TYPE_VOID);
            free(alphanum);
        }
    } while (alphanum != NULL);

    char *op;
    while ((op = lexer_getop(&buffer)) != NULL) {
        printf("Opérateur trouvé : %s\n", op);
        free(op);
    }

    long number;
    while (true) {
        number = lexer_getnumber(&buffer);
        if (number != -1) {
            printf("Number found: %ld\n", number);
        } else {
            break; // Exit loop if no more numbers are found
        }
    }

    // Initialize and test the parser
    printf("\nTesting parser functions:\n");
    parser_t parser;
    parser_init(&parser, &buffer);
    parser.symbol_table = table; // Set the symbol table for the parser

    ast_t *program = parse_program(&parser);

    // Perform semantic analysis on the entire program
    check_type(program, table);

    // Print the AST for testing
    print_ast(program, 0);

    // Clean up
    fclose(file);
    symbol_table_free(table);

    return EXIT_SUCCESS;
}
