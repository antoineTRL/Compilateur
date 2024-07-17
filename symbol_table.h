#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast.h"

typedef struct symbol_table_entry_t {
    char *name;
    var_type_e type;
    struct symbol_table_entry_t *next;
} symbol_table_entry_t;

typedef struct {
    symbol_table_entry_t *entries;
} symbol_table_t;

symbol_table_t *symbol_table_init();
void symbol_table_free(symbol_table_t *table);
symbol_table_entry_t *symbol_table_lookup(symbol_table_t *table, const char *name);
void symbol_table_add(symbol_table_t *table, const char *name, var_type_e type);

#endif // SYMBOL_TABLE_H
