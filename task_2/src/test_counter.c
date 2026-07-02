// ugly, but it is unit-tests, so not so bad
// kernel devs do that, who am i to judge
#include "counter.c"

#include <assert.h>
#include <string.h>

void test_increment_new(void) {
    counter_entry* head = NULL;

    assert(HASH_COUNT(head) == 0);

    counter_increment(&head, "value1", strlen("value1"));
    counter_increment(&head, "value2", strlen("value2"));
    counter_increment(&head, "value3", strlen("value3"));

    assert(HASH_COUNT(head) == 3);

    counter_entry *entry = NULL;
    const char* key = "value2";
    HASH_FIND(hh, head, key, strlen(key), entry);
    assert(entry != NULL);
    assert(entry->value == 1);

    counter_clear(&head);

    printf("test_increment_new passed\n");
}

void test_increment_existing(void) {
    counter_entry* head = NULL;

    assert(HASH_COUNT(head) == 0);

    counter_increment(&head, "value1", strlen("value1"));
    counter_increment(&head, "value1", strlen("value1"));
    counter_increment(&head, "value1", strlen("value1"));
    counter_increment(&head, "value1", strlen("value1"));
    counter_increment(&head, "value1", strlen("value1"));
    counter_increment(&head, "value1", strlen("value1"));

    assert(HASH_COUNT(head) == 1);

    counter_entry *entry = NULL;
    const char* key = "value1";
    HASH_FIND(hh, head, key, strlen(key), entry);
    assert(entry != NULL);
    assert(entry->value == 6);

    counter_clear(&head);

    printf("test_increment_existing passed\n");
}

void test_clear(void) {
    counter_entry* head = NULL;

    assert(HASH_COUNT(head) == 0);

    counter_increment(&head, "value1", strlen("value1"));
    counter_increment(&head, "value2", strlen("value2"));
    counter_increment(&head, "value3", strlen("value3"));

    assert(HASH_COUNT(head) == 3);

    counter_clear(&head);

    assert(HASH_COUNT(head) == 0);

    printf("test_clear passed\n");
}

int main(void) {
    test_increment_new();
    test_increment_existing();
    test_clear();
    return 0;
}