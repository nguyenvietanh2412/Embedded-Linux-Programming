#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int usr_interrupt = 0;

static void handler(int signal) {
    if (signal = SIGUSR1) {
        usr_interrupt = 1;
    }
}
int read_counter(FILE *file) {
    int counter = 0;
    fseek(file, 0, SEEK_SET);
    fscanf(file, "%d", &counter);
    return counter;
}
void write_counter(FILE *file, int counter, __pid_t pid) {
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d\n", counter);
    fprintf(file, "Process ID: %d, counter: %d\n", pid, counter);
}

int main() {
    __pid_t pid;
    int counter = 0;
    FILE *file;
    file = fopen("file.txt", "w+");

    if (file == NULL) {
        printf("Cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGUSR1, handler) == SIG_ERR) {
        perror("Can't catch SIGUSR1.\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("Failed to fork.\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        while (!usr_interrupt) {
            sleep(1);
        }
        counter = read_counter(file);
        counter++;
        write_counter(file, counter, getpid());
    }
    else {
        
        counter++;
        write_counter(file, counter, getpid());
        kill(pid, SIGUSR1);
    }

    fclose(file);
    return 0;
}