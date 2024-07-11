#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbol_table.h"
#include "ast.h"

symbol_table_t *symbol_table_init() {
    symbol_table_t *table = (symbol_table_t *)malloc(sizeof(symbol_table_t));
    if (!table) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    table->head = NULL;
    return table;
}

void symbol_table_add(symbol_table_t *table, char *name, var_type_e type) {
    symbol_table_entry_t *entry = (symbol_table_entry_t *)malloc(sizeof(symbol_table_entry_t));
    if (!entry) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    entry->name = strdup(name);
    if (!entry->name) {
        fprintf(stderr, "Memory allocation failed\n");
        free(entry);
        exit(EXIT_FAILURE);
    }
    entry->type = type;
    entry->next = table->head;
    table->head = entry;
}

symbol_table_entry_t *symbol_table_lookup(symbol_table_t *table, char *name) {
    symbol_table_entry_t *current = table->head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void symbol_table_free(symbol_table_t *table) {
    symbol_table_entry_t *current = table->head;
    while (current) {
        symbol_table_entry_t *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    free(table);
}
