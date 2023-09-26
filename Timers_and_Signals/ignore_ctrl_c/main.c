#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum) {
    printf("\nYou pressed Ctrl+C! But I won't stop.\n");
}

int main() {
    if (signal(SIGINT, handler) == SIG_ERR){
        printf("Failed to set signal handler.");
        return 1;
    }
    printf("Running... Press Ctrl+C to exit\n");

    while(1) {
        sleep(1);
    }

    return 0;
}
