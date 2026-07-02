#define _GNU_SOURCE
#include "process_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>

#define FILENAME 1

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("No input file provided!\n");
        return 1;
    }

    const size_t buffer_size = 4 * 1024;
    static_assert((buffer_size % sizeof(uint32_t)) == 0);

    uint32_t* buffer = NULL;
    uint64_t* seen_once = NULL;
    uint64_t* unique = NULL;

    int input_fd = open(argv[FILENAME], O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open input file.");
        goto clean;
    }

    posix_fadvise(input_fd, 0, 0, POSIX_FADV_SEQUENTIAL);

    seen_once = calloc(total_chunks, sizeof(uint64_t));
    if (seen_once == NULL) {
        perror("seen_once");
        goto clean;
    }

    unique = calloc(total_chunks, sizeof(uint64_t));
    if (unique == NULL) {
        perror("unique");
        goto clean;
    }

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Failed to allocate read buffer.");
        goto clean;
    }

    ssize_t bytes_read = 0;
    do {
        bytes_read = read(input_fd, buffer, buffer_size);
        if (bytes_read < 0) {
            perror("Failed to read from file.");
            goto clean;
        }

        if (bytes_read > 0) {
            //printf("numbers being processed: %zu\n", bytes_read / sizeof(uint32_t));
            int res = process_buffer(buffer, bytes_read / sizeof(uint32_t), unique, seen_once);
            if (res == -1) {
                perror("process_buffer");
                goto clean;
            }
        }
    } while (bytes_read > 0);

    size_t unique_count = 0;
    size_t seen_once_count = 0;
    for (size_t i = 0; i < total_chunks; i++) {
        unique_count += __builtin_popcountll(unique[i]);
        seen_once_count += __builtin_popcountll(seen_once[i]);
    }

    printf("%zu unique numbers\n", unique_count);
    printf("%zu numbers seen only once\n", seen_once_count);

clean:
    free(buffer);
    free(unique);
    free(seen_once);
    if (input_fd >= 0) close(input_fd);
    return 0;
}