#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "lexer.h"
#include "ast.h"
#include "symbol_table.h"

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

    // Call the function from unary_example.c
    printf("\nTesting unary_example function:\n");
    unary_example();



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
        printf("Function Call Node: \n");
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
        free(comp_stmt_node);
    } else {
        printf("Failed to create compound statement node.\n");
    }

    printf("\nTesting ast_new_integer function:\n");
    ast_t *integer_node = ast_new_integer(10);
    printf("AST Node created: Type = %d, Value = %ld\n", integer_node->type, integer_node->integer);

    // Test ast_new_assignment function
    printf("\nTesting ast_new_assignment function:\n");
    assignment_example();

    // Test ast_new_loop function
    printf("\nTesting ast_new_loop function:\n");

    // Create some dummy condition and statement for the loop
    ast_t *loop_condition = ast_new_variable("condition", VAR_TYPE_INT);
    ast_t *loop_stmt = ast_new_variable("stmt", VAR_TYPE_VOID);

    // Create and print loop node
    ast_t *loop_node = ast_new_loop(loop_condition, loop_stmt);
    if (loop_node) {
        printf("Loop Node: %s , %s \n", loop_node->loop.condition->var.name, loop_node->loop.stmt->var.name);
        // Normally, you would also print condition and stmt here if they were populated
        free(loop_node);
    } else {
        printf("Failed to create loop node.\n");
    }

    // Test ast_new_return function
    printf("\nTesting ast_new_return function:\n");

    // Create some dummy expression for the return statement
    ast_t *return_expr = ast_new_variable("returnExpr", VAR_TYPE_INT);

    // Create and print return node
    ast_t *return_node = ast_new_return(return_expr);
    if (return_node) {
        printf("Return Node: %s \n", return_node->ret.expr->var.name);
        // Normally, you would also print expr here if it were populated
        free(return_node);
    } else {
        printf("Failed to create return node \n");
    }

    // Test ast_list_new_node and ast_list_add functions
    printf("\nTesting ast_list_new_node and ast_list_add functions:\n");

    // Create a new AST node for testing
    ast_t *test_node = ast_new_variable("test", VAR_TYPE_INT);

    // Create a new list with the test node
    ast_list_t *list = ast_list_new_node(test_node);
    if (list && list->elem == test_node) {
        printf("List Node created with element name: %s\n", list->elem->var.name);
    } else {
        printf("Failed to create list node.\n");
    }

    // Add another node to the list
    ast_t *another_node = ast_new_variable("anotherNode", VAR_TYPE_VOID);
    ast_list_add(&list, another_node);
    if (list->next && list->next->elem == another_node) {
        printf("Another node added with element name: %s\n", list->next->elem->var.name);
    } else {
        printf("Failed to add another node to the list.\n");
    }

    // Clean up the list
    ast_list_t *current = list;
    while (current) {
        ast_list_t *next = current->next;
        free(current->elem->var.name);
        free(current->elem);
        free(current);
        current = next;
    }

    printf("\nTesting assignment_example function:\n");
    declaration_example();

    printf("\nTesting binary_example function:\n");
    binary_example();

    printf("\nTesting symbol_table functions:\n");
    symbol_table_entry_t *entry = symbol_table_lookup(table, "Ceci");
    if (entry) {
        printf("Found entry: %s, Type: %d\n", entry->name, entry->type);
    } else {
        printf("Entry not found\n");
    }

    entry = symbol_table_lookup(table, "test");
    if (entry) {
        printf("Found entry: %s, Type: %d\n", entry->name, entry->type);
    } else {
        printf("Entry not found\n");
    }

    fclose(file);
    symbol_table_free(table);

    return EXIT_SUCCESS;
}