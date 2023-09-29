#ifndef MY_MALLOC_H_
#define MY_MALLOC_H_
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define META_SIZE sizeof(block_meta_t)
#define MALLOC_MAX_SIZE 4
#define REALLOC_MAX_SIZE 2

typedef struct block_meta_t{
    size_t size;
    struct block_meta_t *next;
    int freed;
}block_meta_t;

void *my_malloc(size_t size);
void my_free(void *ptr);
void *my_realloc(void *ptr, size_t size);
block_meta_t *get_block_ptr(void *ptr);

#endif