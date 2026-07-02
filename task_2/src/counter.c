#include "counter.h"
#include "uthash.h"

#include <stdio.h>

struct counter_entry {
    char* key;
    size_t key_len;
    size_t value;
    UT_hash_handle hh;
};


int counter_increment(counter_entry** head, const char* key, size_t key_len) {
    counter_entry *entry = NULL;
    HASH_FIND(hh, *head, key, key_len, entry);
    if (entry != NULL) {
        entry->value += 1;
    } else {
        entry = malloc(sizeof(counter_entry));
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

void counter_print(counter_entry* head) {
    unsigned int count = HASH_COUNT(head);
    printf("Total entries: %u\n", count);

    counter_entry *current, *tmp;
    HASH_ITER(hh, head, current, tmp) {
        printf("Model: %.*s, Count: %zu\n", 
               (int)current->key_len,
               current->key, 
               current->value);
    }
}


void counter_clear(counter_entry** head) {
    counter_entry *current, *tmp;
    HASH_ITER(hh, *head, current, tmp) {
        HASH_DEL(*head, current);
        free(current->key);
        free(current);
    }
}