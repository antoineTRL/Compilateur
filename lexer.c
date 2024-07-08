#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexer.h"

char *lexer_getalphanum(buffer_t *buffer) {
    char *result = malloc(LEXEM_SIZE + 1); // +1 for null character
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // Exiting here might be harsh; consider another error handling strategy.
    }
    int i = 0;

    buf_skipblank(buffer);

    bool lockAcquired = false;
    if (!buffer->islocked) {
        buf_lock(buffer); // Lock the buffer if not already locked
        lockAcquired = true;
    }

    char c = buf_getchar(buffer);
    while (isalnum(c) && i < LEXEM_SIZE) {
        result[i++] = c;
        c = buf_getchar(buffer);
    }
    result[i] = '\0'; // Ensure string is null-terminated

    if (c != '\0' && lockAcquired) {
        buf_rollback_and_unlock(buffer, 1); // Rollback and unlock if we locked it here
    } else if (lockAcquired) {
        buf_unlock(buffer); // Ensure to unlock if we locked it and didn't rollback
    }

    if (i == 0) { // No alphanum sequence found, free memory and return NULL
        free(result);
        return NULL;
    }

    return result; // Return the found sequence
}

char *lexer_getalphanum_rollback(buffer_t *buffer) {
    //size_t initialPosition = buffer->it; // Sauvegarde de la position initiale du curseur
    buf_lock(buffer); // Verrouillage du buffer pour empêcher les modifications

    // Appel de lexer_getalphanum pour obtenir une séquence alphanumérique, si disponible
    char *result = lexer_getalphanum(buffer);

    // Remet le curseur à sa position initiale, indépendamment du résultat de lexer_getalphanum
    //buffer->it = initialPosition;
    buf_rollback_and_unlock(buffer, buffer->it); // Remet le curseur à sa position initiale et déverrouille le buffer

    return result; // Retourne le résultat obtenu par lexer_getalphanum
}

// Function to get the next operator
char *lexer_getop(buffer_t *buffer) {
    // Operators are defined as per your language's specification
    // This is a placeholder implementation
    char *op = malloc(2); // Assuming single character operators + null terminator
    if (!op) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char c = buf_getchar_after_blank(buffer);
    if (c == '+' || c == '-' || c == '*' || c == '/') {
        op[0] = c;
        op[1] = '\0';
        return op;
    } else {
        free(op);
        return NULL; // No operator found
    }
}

// Function to get the next number
long lexer_getnumber(buffer_t *buffer) {
    // Debugging: Print entry into function
    printf("Debug: lexer_getnumber called.\n");

    char numStr[LEXEM_SIZE + 1];
    int i = 0;
    char c = buf_getchar_after_blank(buffer);

    while (isdigit(c) && i < LEXEM_SIZE) {
        numStr[i++] = c;
        c = buf_getchar(buffer);
    }
    // Ensure the next character is not a digit, if it is, the number might be too long
    if (isdigit(c)) {
        fprintf(stderr, "Number exceeds maximum length.\n");
        return -1; // Might need to handle this case differently
    }
    numStr[i] = '\0';

    if (i == 0) {
        return -1; // Indicates no number was found
    } else {
        return strtol(numStr, NULL, 10); // Convert string to long
    }

    //refactorer cette fonction en utilisant lexer_getalphanum
}