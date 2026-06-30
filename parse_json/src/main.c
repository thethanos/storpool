#define JSMN_STATIC
#include "jsmn.h"
#include "hash_table.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

#define FILENAME 1
#define MODEL 4

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("No input file provided!\n");
        return 1;
    }

    char* json = NULL;
    hash_table_entry *head = NULL;
    const size_t max_tokens = 10;
    jsmntok_t tokens[max_tokens];

    int input_fd = open(argv[FILENAME], O_RDONLY);
    if (input_fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    struct stat file_stat;
    if (fstat(input_fd, &file_stat) < 0) {
        perror("Could not get file size");
        goto clean;
    }


    json = (char*)mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, input_fd, 0);
    if (json == MAP_FAILED) {
        perror("Failed to map file");
        goto clean;
    }

    jsmn_parser parser;
    char* start = NULL, *end = NULL, *cursor = json;
    char* file_end = json + file_stat.st_size;
    while (cursor < file_end) {
        start = memchr(cursor, '{', file_end - cursor);
        if (start == NULL) {
            break;
        }

        end = memchr(start, '}', file_end - start);
        if (end == NULL) {
            // I do not know if the last json object broken intentionally or not
            // but i will assume that not intentionally and just break the loop here
            // Normally, there should be json validation before processing, 
            // since corrupted json objects will affect the outcome and cannot be ignored
            // but it is out of scope of this task
            break;
        }

        cursor = end + 1;

        jsmn_init(&parser);
        if(jsmn_parse(&parser, start, end - start + 1, tokens, max_tokens) < 0) {
            goto clean;
        }

        hash_table_add_or_update_item(&head, start + tokens[MODEL].start, tokens[MODEL].end - tokens[MODEL].start);
    }

    hash_table_print(head); 

clean:
    hash_table_clear(head);
    munmap(json, file_stat.st_size);
    close(input_fd);

    return 0;
}



