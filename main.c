#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "lexer.h"

int main() {
    buffer_t buffer;
    char inputStr[] = "Ceci est un test 12345 avec des mots et des chiffres 67890 + - * / ";
    buf_init_with_string(&buffer, inputStr, strlen(inputStr));

    char *alphanum;
    do {
        alphanum = lexer_getalphanum_rollback(&buffer);
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

    return EXIT_SUCCESS;
}