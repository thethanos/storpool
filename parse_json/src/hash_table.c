#include "hash_table.h"

#include <stdio.h>

struct hash_table_entry {
    char* key;
    size_t key_len;
    size_t value;
    UT_hash_handle hh;
};


int hash_table_add_or_update_item(hash_table_entry** head, const char* key, size_t key_len) {
    hash_table_entry *entry = NULL;
    HASH_FIND(hh, *head, key, key_len, entry);
    if (entry != NULL) {
        entry->value += 1;
    } else {
        entry = malloc(sizeof(hash_table_entry));
        if (entry == NULL) {
            return -1;
        }
        char* key_copy = strndup(key, key_len);
        if (key_copy == NULL) {
            free(entry);
            return -1;
        }
        entry->key = key_copy;
        entry->key_len = key_len;
        entry->value = 1;
        HASH_ADD_KEYPTR(hh, *head, entry->key, key_len, entry);
    }
    return 0;
}

void hash_table_print(hash_table_entry* head) {
    unsigned int count = HASH_COUNT(head);
    printf("Total entries: %u\n", count);

    hash_table_entry *current, *tmp;
    HASH_ITER(hh, head, current, tmp) {
        printf("Key: %.*s, Value: %zu\n", 
               (int)current->key_len,
               current->key, 
               current->value);
    }
}


void hash_table_clear(hash_table_entry* head) {
    hash_table_entry *current, *tmp;
    HASH_ITER(hh, head, current, tmp) {
        HASH_DEL(head, current);
        free(current->key);
        free(current);
    }
}