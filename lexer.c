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

    char *alphanumStr = lexer_getalphanum(buffer);

    if (alphanumStr == NULL) {
        return -1; // Indicates no alphanum sequence was found
    }

    // Check if the alphanumStr consists only of digits
    for (int i = 0; alphanumStr[i] != '\0'; i++) {
        if (!isdigit(alphanumStr[i])) {
            free(alphanumStr); // Free the allocated memory
            return -1; // Indicates that the sequence is not a valid number
        }
    }

    long number = strtol(alphanumStr, NULL, 10); // Convert string to long
    free(alphanumStr); // Free the allocated memory
    return number;
}