#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Received SIGUSR1 signal.\n");
    }
}

int main() {
    // Set up a signal handler for SIGUSR1
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    // Set up a timer to send SIGUSR1 at a specific time
    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGUSR1;

    timer_t timerid;
    timer_create(CLOCK_REALTIME, &sev, &timerid);

    struct itimerspec its;
    its.it_value.tv_sec = 5;  // Set the timer to trigger after 5 seconds
    its.it_value.tv_nsec = 0;
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    timer_settime(timerid, 0, &its, NULL);

    printf("Waiting for the signal...\n");
    int count = 0;
    while (1) {
        // Keep the program running
        printf("Program is still running %d\n", count);
        count++;
        sleep(1);
    }

    return 0;
}