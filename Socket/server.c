// Server code in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080 // The port number for the server
#define MAX 1024 // The maximum size of the buffer

// A function to reverse a string
void reverse(char* str, int len) {
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

// A function to handle the communication with a client
void handle_client(int sock) {
    char buffer[MAX]; // The buffer to store the messages
    int n; // The number of bytes received or sent

    // Loop until the client closes the connection
    while (1) {
        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));

        // Receive a message from the client
        n = read(sock, buffer, sizeof(buffer));
        if (n <= 0) {
            // If no bytes are received or an error occurs, close the socket and exit the function
            printf("Client disconnected.\n");
            close(sock);
            return;
        }

        // Print the received message
        printf("Received from client: %s\n", buffer);

        // Reverse the message
        reverse(buffer, strlen(buffer));

        // Send the reversed message back to the client
        n = write(sock, buffer, strlen(buffer));
        if (n <= 0) {
            // If no bytes are sent or an error occurs, close the socket and exit the function
            printf("Client disconnected.\n");
            close(sock);
            return;
        }

        // Print the sent message
        printf("Sent to client: %s\n", buffer);
    }
}

int main() {
    int server_fd, client_fd; // The file descriptors for the server and client sockets
    struct sockaddr_in server_addr, client_addr; // The structures to store the server and client addresses
    socklen_t client_len; // The length of the client address

    // Create a socket for the server
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        // If an error occurs, print an error message and exit the program
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the server address parameters
    server_addr.sin_family = AF_INET; // The address family is IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // The server can accept connections from any IP address
    server_addr.sin_port = htons(PORT); // The port number is converted to network byte order

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        // If an error occurs, print an error message and exit the program
        perror("Socket binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections on the socket
    if (listen(server_fd, 5) == -1) {
        // If an error occurs, print an error message and exit the program
        perror("Socket listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    // Loop forever to accept and handle connections from clients
    while (1) {
        // Accept a connection from a client
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            // If an error occurs, print an error message and continue to the next iteration
            perror("Socket acceptance failed");
            continue;
        }

        printf("Client connected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Handle the communication with the client in a separate function
        handle_client(client_fd);
    }

    return 0;
}
