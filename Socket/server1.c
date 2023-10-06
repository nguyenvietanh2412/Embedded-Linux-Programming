#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#define BACK_LOG 3
#define PORT 1800
#define MAX_SIZE_BUFFER 1024

void reverse(char *str, int len) {
    int i = 0;
    int j = len - 1;
    int temp;
    for (i; i < len; i++) {
        str[i] = toupper(str[i]);
    }
    i = 0;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
void handle_client(int sock) {
    char buffer[MAX_SIZE_BUFFER];
    

    while(1) {
        memset(buffer, 0 , sizeof(buffer));
        if (read(sock, buffer, sizeof(buffer)) <= 0) {
            printf("Client said \"CUT\".....\n");
            close(sock);
            return;
        }

        printf("Received from client: %s\n", buffer);

        reverse(buffer, strlen(buffer));

        if (write(sock, buffer, strlen(buffer)) <= 0) {
            printf("Client disconnected\n");
            close(sock);
            return;
        }

        printf("Sent to client: %s\n", buffer);
    }

}
int main() {
    int server_fd;
    int client_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t server_len;
    socklen_t client_len;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed:");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET; // The address family is IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // The server can accept connections from any IP address
    server_addr.sin_port = htons(PORT); // The port number is converted to network byte order

    server_len = sizeof(server_addr);
    if (bind(server_fd, (struct sockaddr*)&server_addr, server_len) == -1) {
        perror("Bind failed:");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, BACK_LOG) == -1) {
        perror("Listen failed:");
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d\n", PORT);
    while(1) {
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*) &client_addr, &client_len);
        if (client_fd == -1) {
            perror("Accept failed:");
            continue;
        }
        printf("Connect to client at adress: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        handle_client(client_fd);
    }
    return 0;
}