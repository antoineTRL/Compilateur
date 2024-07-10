#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "lexer.h"
#include "ast.h"

int main() {
    buffer_t buffer;
    FILE *file = fopen("example.txt", "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return EXIT_FAILURE;
    }

    buf_init(&buffer, file); // Ensure buffer is initialized


    char *alphanum;
    do {
        alphanum = lexer_getalphanum(&buffer);
        if (alphanum) {
            printf("Séquence alphanumérique trouvée : %s\n", alphanum);
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

    // Call the function from unary_example.c
    printf("\nTesting unary_example function:\n");
    unary_example();

    fclose(file);

    // Test ast_new_variable function
    printf("\nTesting ast_new_variable function:\n");

    // Create and print variable node for VAR_TYPE_INT
    ast_t *var_node_int = ast_new_variable("x", VAR_TYPE_INT);
    if (var_node_int) {
        printf("Variable Node (INT):\n");
        printf("Name: %s\n", var_node_int->var.name);
        printf("Type: %d\n", var_node_int->var.type);
        free(var_node_int->var.name);
        free(var_node_int);
    } else {
        printf("Failed to create variable node (INT).\n");
    }

    // Create and print variable node for VAR_TYPE_VOID
    ast_t *var_node_void = ast_new_variable("y", VAR_TYPE_VOID);
    if (var_node_void) {
        printf("Variable Node (VOID):\n");
        printf("Name: %s\n", var_node_void->var.name);
        printf("Type: %d\n", var_node_void->var.type);
        free(var_node_void->var.name);
        free(var_node_void);
    } else {
        printf("Failed to create variable node (VOID).\n");
    }

    // Test ast_new_function function
    printf("\nTesting ast_new_function function:\n");

    // Create some dummy parameter and statement lists for the function
    ast_list_t *params = NULL;
    ast_list_t *stmts = NULL;

    // Create and print function node
    ast_t *func_node = ast_new_function("myFunction", VAR_TYPE_INT, params, stmts);
    if (func_node) {
        printf("Function Node:\n");
        printf("Name: %s\n", func_node->function.name);
        printf("Return Type: %d\n", func_node->function.return_type);
        // Normally, you would also print params and stmts here if they were populated
        free(func_node->function.name);
        free(func_node);
    } else {
        printf("Failed to create function node.\n");
    }

    // Test ast_new_fncall function
    printf("\nTesting ast_new_fncall function:\n");

    // Create some dummy argument list for the function call
    ast_list_t *args = NULL;

    // Create and print function call node
    ast_t *fncall_node = ast_new_fncall("callFunction", args);
    if (fncall_node) {
        printf("Function Call Node:\n");
        printf("Name: %s\n", fncall_node->call.name);
        // Normally, you would also print args here if they were populated
        free(fncall_node->call.name);
        free(fncall_node);
    } else {
        printf("Failed to create function call node.\n");
    }

    // Test ast_new_comp_stmt function
    printf("\nTesting ast_new_comp_stmt function:\n");

    // Create some dummy statement list for the compound statement
    ast_list_t *comp_stmts = NULL;

    // Create and print compound statement node
    ast_t *comp_stmt_node = ast_new_comp_stmt(comp_stmts);
    if (comp_stmt_node) {
        printf("Compound Statement Node:\n");
        // Normally, you would also print stmts here if they were populated
        free(comp_stmt_node);
    } else {
        printf("Failed to create compound statement node.\n");
    }

    printf("\nTesting ast_new_integer function:\n");
    ast_t *integer_node = ast_new_integer(40);
    printf("AST Node created: Type = %d, Value = %ld\n", integer_node->type, integer_node->integer);

    return EXIT_SUCCESS;
}