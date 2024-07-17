#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "lexer.h"
#include "ast.h"
#include "symbol_table.h"
#include "parser.h"
#include "semantic.h"
#include "codegen.h"
#include "print_ast.h" // Include the new header file

int main() {
    buffer_t buffer;
    FILE *file = fopen("intech.txt", "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return EXIT_FAILURE;
    }

    buf_init(&buffer, file); // Ensure buffer is initialized
    symbol_table_t *table = symbol_table_init();

    // Initialize and test the parser
    printf("\nTesting parser functions:\n");
    parser_t parser;
    parser_init(&parser, &buffer);

    ast_t *program = parse_program(&parser);

    // Print the AST for testing
    printf("\nAbstract Syntax Tree (AST):\n");
    print_ast(program, 0);

    // Perform semantic analysis
    printf("\nPerforming semantic analysis:\n");
    if (!semantic_analysis(program, table)) {
        fprintf(stderr, "Semantic analysis failed\n");
        return EXIT_FAILURE;
    }

    // Generate intermediate code
    printf("\nGenerating intermediate code:\n");
    generate_code(program);

    // Clean up
    fclose(file);
    symbol_table_free(table);

    return EXIT_SUCCESS;
}
