#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int sig) {
    printf("Received signal %d\n", sig);
    printf("Child's PPID: %d\n", getppid());
    fflush(stdout);  // Flush the output buffer
}

int main() {
    // Create child process
    int pid = fork();

    if (pid > 0) {
        // If pid is greater than 0, it means the parent process is running.
        printf("In parent process\n");
        sleep(10); // Sleep for 10 seconds
    }
    else if (pid == 0) {
        // If pid is 0, then it means this is the child process.
        printf("In child process\n");
        printf("Child PID: %d\n", getpid());
        fflush(stdout);  // Flush the output buffer

        // Set up signal handler
        struct sigaction sa;
        sa.sa_handler = &handle_signal;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("sigaction");
            return 1;
        }

        // Pause to wait for signal
        while(1) {
            pause();
        }
    }

    return 0;
}
