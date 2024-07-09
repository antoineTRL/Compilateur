#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "lexer.h"
#include "Ast.h"

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
    unary_example();

    fclose(file);
    return EXIT_SUCCESS;
}