#include "my_malloc.h"

int main(){
    // Allocate memory by my_malloc()
    int *x = (int *)my_malloc(MALLOC_MAX_SIZE * sizeof(int));

    // Get size of the memory just allocated by my_malloc()
    block_meta_t* x_meta = get_block_ptr(x);
    printf("Size by malloc: %zu\n", x_meta->size);

    for (int i = 0; i < MALLOC_MAX_SIZE; i++) {
        printf("x[%d]:", i);
        scanf("%d", &x[i]);
    }

    printf("x:\n");

    for (int i = 0; i < MALLOC_MAX_SIZE; i++) {
        printf("%d  ", x[i]);
    }
    // Reallocate memory by my_realloc()
    x = my_realloc(x, REALLOC_MAX_SIZE * sizeof(int));

    // Get size of the memory just reallocated
    x_meta = get_block_ptr(x);
    printf("\nSize by realloc: %zu\n", x_meta->size);
    printf("x:\n");

    for (int i = 0; i < REALLOC_MAX_SIZE; i++) {
        printf("%d  ", x[i]);
    }

    printf("\n");

    // Free memory by my_free() and assign the pointer to NULL
    my_free(x);
    x = NULL;

    return 0;
}