#include "multithread.h"

int main(){

    double non_threaded_time;
    double multithread_time;

    // Allocate memories for matrices
    A = allocate_matrix(M, N);
    B = allocate_matrix(N, P);
    C = allocate_matrix(M, P);

    // Create random values for matrices' elements
    create_random_element(A, M, N);
    printf("Random matrix A:\n");
    show_matrix(A, M, N);
    
    create_random_element(B, N, P);
    printf("Random matrix B:\n");
    show_matrix(B, N, P);

    // Multiply two matrices by non-threaded method and calculate time
    non_threaded_time = multiply_matrix_non_thread();
    printf("\nMatrix C calculated by NON-THREAD:\n");
    show_matrix(C, N, P);

    // Multiply two matrices by threaded method and calculate time
    multithread_time = multiply_matrix_multithread();
    printf("Matrix C calculated by MULTITHREAD:\n");
    show_matrix(C, N, P);

    printf("\nTime calculated by NON-THREAD: %f\n", non_threaded_time);
    printf("Time calculated by MULTITHREAD: %f\n\n", multithread_time);

    if (non_threaded_time < multithread_time){
        printf("Non-thread is FASTER than multithread.\n");
    }
    else if (non_threaded_time > multithread_time){
        printf("Non-thread is LOWER than multithread.\n");
    }
    else{
        printf("Both methods have the same speed.\n\n");
    }

    free_matrix(A, M);
    free_matrix(B, N);
    free_matrix(C, M);

    return 0;
}
