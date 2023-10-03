#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>

#define MAX_THREADS 3
#define MAX_COUNT 5

static int glob = 0;
static sem_t sem[MAX_THREADS];
FILE *file_1, *file_2;

static void *increment(void *arg){
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&sem[0]);
        glob+=2;
        printf("Increment glob to: %d   ", glob);
        printf("Pthread id: %lu\n", pthread_self());
        sem_post(&sem[2]);
    }
    return NULL;
}

static void *decrement(void *arg){
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&sem[1]);
        glob--;
        printf("Decrement glob to: %d   ", glob);
        printf("Pthread id: %lu\n\n", pthread_self());
        sem_post(&sem[0]);
    }
    return NULL;
}

static void *multiply(void *arg){
    for (int i = 0; i < MAX_COUNT; i++) {
        sem_wait(&sem[2]);
        glob *= 2;
        printf("Multiply glob to: %d   ", glob);
        printf("Pthread id: %lu\n", pthread_self());
        sem_post(&sem[1]);
    }
    return NULL;
}

int main(){
    pthread_t threads[MAX_THREADS];
    int thread_nums[MAX_THREADS];
    if (sem_init(&sem[0], 0, 1) == -1){
        perror("Initialize semaphore failed:");
    }
    if (sem_init(&sem[1], 0, 0) == -1){
        perror("Initialize semaphore failed:");
    }
    if (sem_init(&sem[2], 0, 0) == -1){
        perror("Initialize semaphore failed:");
    }
    for (int i = 0; i < MAX_THREADS; i++) {
        thread_nums[i] = i;
    }
    
    pthread_create(&threads[0], NULL, increment, &thread_nums[0]);
    pthread_create(&threads[1], NULL, decrement, &thread_nums[1]);
    pthread_create(&threads[2], NULL, multiply, &thread_nums[2]);

    for (int i = 0; i < MAX_THREADS; i++){
        pthread_join(threads[i], NULL);
        sem_destroy(&sem[i]);
    }
    
    return 0;
}
