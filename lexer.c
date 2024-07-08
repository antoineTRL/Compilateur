#include <ctype.h>
#include <stdlib.h>
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