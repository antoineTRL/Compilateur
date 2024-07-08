//
// Created by Antoine on 08/07/2024.
//

#ifndef COMPILATEUR_LEXER_H
#define COMPILATEUR_LEXER_H

#include "buffer.h"

        char *lexer_getalphanum(buffer_t *buffer);
        char *lexer_getalphanum_rollback(buffer_t *buffer);
        char *lexer_getop(buffer_t *buffer);
        long lexer_getnumber(buffer_t *buffer);


#endif //COMPILATEUR_LEXER_H
