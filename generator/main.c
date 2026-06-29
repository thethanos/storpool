#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int main(int argc, char** argv) {
    printf("argc: %d, argv: %s\n", argc, argv[0]);

    size_t buffer_size = 100000;
    size_t bytes_read = 0;
    size_t bytes_required = 1073741824  * sizeof(uint32_t);
    uint32_t buffer[buffer_size];

    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /dev/urandom");
        return 1;
    }

    FILE* output = fopen("test_file.bin", "ab");
    if (!output) {
        perror("Failed to open output file");
        goto clean;
    }

    while (bytes_required > 0) {
        size_t bytes_read = read(fd, buffer, buffer_size);
        if (bytes_read == 0) {
            perror("Error reading from /dev/urandom");
            goto clean;
        }

        size_t bytes_written = fwrite(buffer, sizeof(uint32_t), bytes_read, output);
        if (bytes_written < buffer_size) {
            perror("Failed to write to the file");
            goto clean;
        }
        bytes_required -= bytes_read;
        printf("bytes left: %ld\n", bytes_required);
    }

clean:
    fclose(output);
    close(fd);
    
    return 0;
}