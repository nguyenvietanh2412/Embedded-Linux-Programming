#include "daemon.h"

int start_daemon(){
    FILE *filepath;
    pid_t pid = 0;
    pid_t sid = 0;
    int count = 0;
    pid = fork();

    if (pid < 0){
        printf("Fork failed!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0){
        printf("Process id of child process: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    umask(0);

    if (chdir("/") < 0){
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    filepath = fopen("/home/andy_nguyen/Documents/login.log", "a+");
    while(count < MAX){
        fprintf(filepath, "User: %s     ID: %d\n", getlogin(), getuid());
        fflush(filepath);
        count += 1;
        sleep(1);
    }
    fclose(filepath);
}