#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define PORT 1800
#define MAX_SIZE_BUFFER 1024

int main() {
    int sock;
    char buffer[MAX_SIZE_BUFFER];
    struct sockaddr_in server_addr;
    socklen_t server_len;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket in client failed:");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    server_len = sizeof(server_addr);

    if (connect(sock, (struct sockaddr *) &server_addr, server_len)) {
        perror("Connect to server failed:");
        exit(EXIT_FAILURE);
    }

    printf("Connect to server at adress %s:%d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));
    while(1) {
        memset(buffer, 0, sizeof(buffer));

        printf("Enter your message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "exit") == 0) {
            printf("Disconnect client............\n");
            close(sock);
            break;
        }

        if (write(sock, buffer, strlen(buffer)) <= 0) {
            perror("Client writing failed:");
            exit(EXIT_FAILURE);
        }

        printf("Message sent to server: %s\n", buffer);
        
        memset(buffer, 0 , sizeof(buffer));

        if (read(sock, buffer, sizeof(buffer)) <= 0) {
            perror("Read from server failed:");
            exit(EXIT_FAILURE);
        }

        printf("Message received from server: %s\n", buffer);

    }
    return 0;
}