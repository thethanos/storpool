#ifndef COUNTER_H
#define COUNTER_H

#include <stddef.h>

typedef struct counter_entry counter_entry;

int counter_increment(counter_entry** head, const char* key, size_t key_len);

void counter_print(counter_entry* head);

void counter_clear(counter_entry** head);

#endif // COUNTER_H