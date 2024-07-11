#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast.h"

typedef struct symbol_table_entry_t {
    char *name;
    var_type_e type;
    struct symbol_table_entry_t *next;
} symbol_table_entry_t;

typedef struct {
    symbol_table_entry_t *head;
} symbol_table_t;

// Function prototypes
symbol_table_t *symbol_table_init();
void symbol_table_add(symbol_table_t *table, char *name, var_type_e type);
symbol_table_entry_t *symbol_table_lookup(symbol_table_t *table, char *name);
void symbol_table_free(symbol_table_t *table);

#endif // SYMBOL_TABLE_H