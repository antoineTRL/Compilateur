#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
#include "lexer.h"

int main() {
    // Initialiser le buffer avec une chaîne de caractères
    buffer_t buffer;
    char inputStr[] = "Il manque le dernier mot";
    buf_init_with_string(&buffer, inputStr, strlen(inputStr));

    // Lire et afficher une séquence alphanumérique
    char *alphanum = lexer_getalphanum(&buffer);
    while (alphanum) {
        printf("Sequence alphanumerique trouvee : %s\n", alphanum);
        free(alphanum); // Libérer la mémoire allouée par lexer_getalphanum
        alphanum = lexer_getalphanum(&buffer);
    }

    return EXIT_SUCCESS;
}