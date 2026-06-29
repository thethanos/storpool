#ifndef PROCESS_BUFFER_H
#define PROCESS_BUFFER_H

#include <stdint.h>
#include <stddef.h>

extern const size_t total_chunks; 

int process_buffer(const uint32_t* buffer, const size_t numbers_read, uint64_t* unique, uint64_t* seen_once);

#endif // PROCESS_BUFFER_H