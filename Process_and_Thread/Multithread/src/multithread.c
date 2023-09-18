#include "multithread.h"

int **A;
int **B;
int **C;
void create_random_element(int **matrix, int row, int col){
    srand(time(NULL));
    int i;
    int j;
    for (i = 0; i < row; i++){
        for (j = 0 ;j < col; j++){
            matrix[i][j] = rand() % 10;
        }
    }
}
int **allocate_matrix(int row, int col){
    int **matrix;
    int i;
    matrix = (int **)malloc(row * sizeof(int *));

    for (i = 0; i < row; i++){
        matrix[i] = (int *)malloc(col * sizeof(int));
    }

    return matrix;
}
void multiply_column_non_thread(int col){
    int i;
    int j;
    for (i = 0; i < M; i++){
        C[i][col] = 0;
        for (j = 0; j < N; j++){
            C[i][col] += A[i][j] * B[j][col];
        }
    }
}
void *multiply_column_multithread(void *arg){
    __intptr_t col = (__intptr_t) arg;

    int i;
    int j;
    for (i = 0; i < M; i++){
        C[i][col] = 0;
        for (j = 0; j < N; j++){
            C[i][col] += A[i][j] * B[j][col];
        }
    }
    pthread_exit(0);
}
double multiply_matrix_non_thread(){
    int i;
    clock_t start, end;

    start = clock();

    for (i = 0; i < P; i++){
        multiply_column_non_thread(i);
    }

    end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}
double multiply_matrix_multithread(){
    int i;
    clock_t start;
    clock_t end;
    pthread_t threads[P];
    start = clock();

    for (i = 0; i < P; i++){
        pthread_create(&threads[i], NULL, multiply_column_multithread, (void *)(__intptr_t) i);
    }
    for (i = 0; i < P; i++){
        pthread_join(threads[i], NULL);
    }

    end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}
void show_matrix(int **matrix, int row, int col){
    int i;
    int j;
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void free_matrix(int **matrix, int row){
    int i;
    
    for (i = 0; i < row; i++){
        free(matrix[i]);
        matrix[i]= NULL;
    }
    free(matrix);
    matrix = NULL;
}