#include "process_buffer.h"

#include <stdbool.h>
#include <errno.h>

const size_t total_chunks = (1ULL << 32) / 64; 

static bool check_bit(const uint64_t* bitmap_chunk, const uint8_t bit_num) {
    return *bitmap_chunk & (1ULL << bit_num);
}

static void set_bit(uint64_t* bitmap_chunk, const uint8_t bit_num) {
    uint64_t bit_mask = (1ULL << bit_num);
    *bitmap_chunk |= bit_mask;
}

static void reset_bit(uint64_t* bitmap_chunk, const uint8_t bit_num) {
    uint64_t bit_mask = ~(1ULL << bit_num);
    *bitmap_chunk &= bit_mask;
}

int process_buffer(const uint32_t* buffer, const size_t numbers_read, uint64_t* unique, uint64_t* seen_once) {

    if (!buffer || !unique || !seen_once) {
        errno = EINVAL;
        return -1;
    }

    for (size_t i = 0; i < numbers_read; i++) {
        size_t chunk_num = buffer[i] / 64;
        size_t bit_num = buffer[i] % 64;

        if (!check_bit(&unique[chunk_num], bit_num)) {
            set_bit(&unique[chunk_num], bit_num);
            set_bit(&seen_once[chunk_num], bit_num);
        } else if (check_bit(&seen_once[chunk_num], bit_num)) {
            reset_bit(&seen_once[chunk_num], bit_num);
        }
    }
    return 0;
}