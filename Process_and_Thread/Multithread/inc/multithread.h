#ifndef MULTITHREAD_H_
#define MULTITHREAD_H_
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 3 // rows of 1st matrix
#define N 2 // columns of 1st mtstrix = rows of 2nd matrix
#define P 3 // rows of 2nd matrix

extern int **A;
extern int **B;
extern int **C;

int **allocate_matrix(int row, int col);
double multiply_matrix_non_thread();
double multiply_matrix_multithread();
void create_random_element(int **matrix, int row, int col);
void free_matrix(int **matrix, int row);
void show_matrix(int **matrix, int row, int col);
#endif