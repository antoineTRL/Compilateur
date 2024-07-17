#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

symbol_table_t *symbol_table_init() {
    symbol_table_t *table = (symbol_table_t *)malloc(sizeof(symbol_table_t));
    table->entries = NULL;
    return table;
}

void symbol_table_free(symbol_table_t *table) {
    symbol_table_entry_t *entry = table->entries;
    while (entry) {
        symbol_table_entry_t *next = entry->next;
        free(entry->name);
        free(entry);
        entry = next;
    }
    free(table);
}

symbol_table_entry_t *symbol_table_lookup(symbol_table_t *table, const char *name) {
    symbol_table_entry_t *entry = table->entries;
    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

void symbol_table_add(symbol_table_t *table, const char *name, var_type_e type) {
    symbol_table_entry_t *entry = (symbol_table_entry_t *)malloc(sizeof(symbol_table_entry_t));
    entry->name = strdup(name);
    entry->type = type;
    entry->next = table->entries;
    table->entries = entry;
}
