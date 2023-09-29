#include "my_malloc.h"

void *global_base = NULL;

static block_meta_t *find_free_block(block_meta_t **last, size_t size){
    block_meta_t *current = global_base;

    // Traverse the linked list of blocks until a free block of sufficient size is found
    while (current && !(current->freed && current->size >= size)) {
    *last = current;
    current = current->next;
    }
    return current;
}

static block_meta_t *request_block(block_meta_t *last, size_t size){
    block_meta_t *block;

    // Get the current break point
    block = sbrk(0);

    // Request additional memory
    void *request = sbrk(size + META_SIZE);

    // Ensure that the memory was allocated as expected
    assert((void*)block == request);
    if (request == (void*) -1) {
        return NULL;
    }

    // If this isn't the first block, link it to the previous one
    if (last) {
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->freed = 0;
    return block;
}

void *my_malloc(size_t size) {
    block_meta_t *block;
    if (size <= 0) {
        return NULL;
    }

    // If this is the first allocation, request a new block
    if (!global_base) {
        block = request_block(NULL, size);
        if (!block) {
            return NULL;
        }
        global_base = block;
    } else {
        block_meta_t *last = global_base;

        // Find a free block of sufficient size
        block = find_free_block(&last, size);
        if (!block) {

            // If no suitable free block was found, request a new one
            block = request_block(last, size);
            if (!block) {
                return NULL;
            }
        } else {
            // If the existing block is larger than the requested size plus the size of the metadata structure,
            // split the block into two.
            if (block->size >= size + sizeof(block_meta_t)) {
                block_meta_t *new_block = (block_meta_t*)((char*)block + sizeof(block_meta_t) + size);
                new_block->size = block->size - size - sizeof(block_meta_t);
                new_block->next = block->next;
                new_block->freed = 1;

                block->size = size;
                block->next = new_block;
            }

            // Mark the allocated block as not free
            block->freed = 0;
        }
    }

    // Return a pointer to the usable memory area within the allocated block
    return(block + 1);
}

// Function to get a pointer to a memory area's metadata given a pointer to its usable area
block_meta_t *get_block_ptr(void *ptr) {
    return (block_meta_t*)ptr - 1;
}
void my_free(void *ptr) {
    
    if (!ptr) {
        return;
    }

    // Get a pointer to ptr's metadata and mark its associated memory area as free
    block_meta_t* block_ptr = get_block_ptr(ptr);
    assert(block_ptr->freed == 0);
    block_ptr->freed = 1;
}

void *my_realloc(void *ptr, size_t size) {
    if (!ptr) {
        return my_malloc(size);
    }

    block_meta_t *block_ptr = get_block_ptr(ptr);

    // Check iff the existing block is large enough
    if (block_ptr->size >= size) {

        // If the existing block is larger than the requested size plus the size of the metadata structure,
        // split the block into two.
        if (block_ptr->size >= size + sizeof(block_meta_t)) {
            block_meta_t *new_block = (block_meta_t*)((char*)block_ptr + sizeof(block_meta_t) + size);
            new_block->size = block_ptr->size - size - sizeof(block_meta_t);
            new_block->next = block_ptr->next;
            new_block->freed = 1;

            block_ptr->size = size;
            block_ptr->next = new_block;
        }
        return ptr;
    }

    void *new_ptr;

    // Allocate a new block of memory
    new_ptr = my_malloc(size);

    if (!new_ptr) {
        return NULL;
    }

    // Copy the contents of the old memory area to the new one
    memcpy(new_ptr, ptr, block_ptr->size);

    // Free the old memory area
    my_free(ptr);

    // Return a pointer to the new memory area
    return new_ptr;
}
