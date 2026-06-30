#ifndef HASH_TABLE
#define HASH_TABLE

#include "uthash.h"

typedef struct hash_table_entry hash_table_entry;

int hash_table_add_or_update_item(hash_table_entry** head, const char* key, size_t key_len);

void hash_table_print(hash_table_entry* head);

void hash_table_clear(hash_table_entry* head);

#endif // HASH_TABLE