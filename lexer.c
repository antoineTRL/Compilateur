#include "lexer.h"
#include "buffer.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// Function to get the next character
static char buffer_next_char(buffer_t *buffer) {

}

char *lexer_getalphanum(buffer_t *buffer) {
    char *result = malloc(LEXEM_SIZE+1); // +1 pour le caractère null
    if (!result) {
        fprintf(stderr, "Erreur de compilation : Échec d'allocation mémoire\n");
        exit(EXIT_FAILURE);  // Quitter le programme en cas d'erreur
    }
    int i = 0; // Initialiser l'index

    // Skip whitespace
    buf_skipblank(buffer);

    char c = buf_getchar(buffer); // Obtenir le premier caractère
    while (isalnum(c) && i < LEXEM_SIZE) { // Vérifier si c'est alphanumérique et dans la limite
        result[i++] = c;
        c = buf_getchar(buffer); // Obtenir le caractère suivant
    }
    buf_rollback(buffer, 1); // Revenir d'un caractère si non alphanumérique

    result[i] = '\0'; // Terminer la chaîne
    return result; // Retourner le résultat

}

char *lexer_getalphanum_rollback(buffer_t *buffer) {


    // Skip whitespace
    buf_skipblank(buffer);


}

char *lexer_getop(buffer_t *buffer) {


    // Rewind if no valid operator characters found

}

long lexer_getnumber(buffer_t *buffer) {

    return 0;
}
