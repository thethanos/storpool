#include "process_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char** argv) {

    if (argc < 2) {
        printf("No input file provided!\n");
        return 1;
    }

    // big buffer to reduce amount of system calls
    // if we are poor, this constant can be adjusted
    const size_t buffer_size = 104857610; 
    uint32_t* buffer = NULL;
    uint64_t* seen_once = NULL;
    uint64_t* unique = NULL;

    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open input file.");
        goto clean;
    }

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

    buffer = malloc(buffer_size * sizeof(uint32_t));
    if (buffer == NULL) {
        perror("Failed to allocate read buffer.");
        goto clean;
    }

    ssize_t bytes_read = 0;
    do {
        bytes_read = read(input_fd, buffer, buffer_size * sizeof(uint32_t));
        if (bytes_read < 0) {
            perror("Failed to read from file.");
            goto clean;
        }

        if (bytes_read > 0) {
            printf("numbers being processed: %zd\n", bytes_read / sizeof(uint32_t));
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

    printf("%zd unique numbers\n", unique_count);
    printf("%zd numbers seen only once\n", seen_once_count);

clean:
    free(buffer);
    free(unique);
    free(seen_once);
    if (input_fd >= 0) close(input_fd);
    return 0;
}