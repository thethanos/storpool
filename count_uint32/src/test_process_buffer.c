#include "process_buffer.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void test_null_arguments()
{
    uint32_t buffer[] = {1};
    uint64_t unique[2] = {0};
    uint64_t seen_once[2] = {0};

    assert(process_buffer(NULL, 1, unique, seen_once) == -1);
    assert(errno == EINVAL);
    errno = 0;

    assert(process_buffer(buffer, 1, NULL, seen_once) == -1);
    assert(errno == EINVAL);
    errno = 0;

    assert(process_buffer(buffer, 1, unique, NULL) == -1);
    assert(errno == EINVAL);
    errno = 0;

    printf("test_null_arguments passed\n");
}


void test_empty_buffer()
{
    uint32_t buffer[] = {};

    uint64_t unique[1] = {0};
    uint64_t seen_once[1] = {0};

    assert(process_buffer(buffer, 0, unique, seen_once) == 0);

    assert(unique[0] == 0);
    assert(seen_once[0] == 0);

    printf("test_empty_buffer passed\n");
}


void test_single_number()
{
    uint32_t buffer[] = {10};

    uint64_t unique[1] = {0};
    uint64_t seen_once[1] = {0};

    assert(process_buffer(buffer, 1, unique, seen_once) == 0);

    assert(__builtin_popcountll(unique[0]) == 1);
    assert(__builtin_popcountll(seen_once[0]) == 1);

    printf("test_single_number passed\n");
}


void test_duplicate()
{
    uint32_t buffer[] = {10, 10};

    uint64_t unique[1] = {0};
    uint64_t seen_once[1] = {0};

    assert(process_buffer(buffer, 2, unique, seen_once) == 0);

    assert(__builtin_popcountll(unique[0]) == 1);
    assert(__builtin_popcountll(seen_once[0]) == 0);

    printf("test_duplicate passed\n");
}


void test_multiple_duplicates()
{
    uint32_t buffer[] = {10, 10, 10};

    uint64_t unique[1] = {0};
    uint64_t seen_once[1] = {0};

    assert(process_buffer(buffer, 3, unique, seen_once) == 0);

    assert(__builtin_popcountll(unique[0]) == 1);
    assert(__builtin_popcountll(seen_once[0]) == 0);

    printf("test_multiple_duplicates passed\n");
}


void test_mixed_values()
{
    uint32_t buffer[] = {1, 1, 2, 3, 4, 4, 5};

    uint64_t unique[1] = {0};
    uint64_t seen_once[1] = {0};

    assert(process_buffer(buffer, 7, unique, seen_once) == 0);

    assert(__builtin_popcountll(unique[0]) == 5);
    assert(__builtin_popcountll(seen_once[0]) == 3);

    printf("test_mixed_values passed\n");
}


void test_multiple_chunks()
{
    uint32_t buffer[] = {10, 64, 70, 64};

    uint64_t unique[2] = {0};
    uint64_t seen_once[2] = {0};

    assert(process_buffer(buffer, 4, unique, seen_once) == 0);

    assert(__builtin_popcountll(unique[0]) == 1);
    assert(__builtin_popcountll(unique[1]) == 2);

    assert(__builtin_popcountll(seen_once[0]) == 1);
    assert(__builtin_popcountll(seen_once[1]) == 1);

    printf("test_multiple_chunks passed\n");
}

int main()
{
    test_null_arguments();
    test_empty_buffer();
    test_single_number();
    test_duplicate();
    test_multiple_duplicates();
    test_mixed_values();
    test_multiple_chunks();

    return 0;
}