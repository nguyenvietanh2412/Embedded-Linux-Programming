// Client code in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080 // The port number for the server
#define MAX 1024 // The maximum size of the buffer

int main() {
    int sock; // The file descriptor for the client socket
    struct sockaddr_in server_addr; // The structure to store the server address
    char buffer[MAX]; // The buffer to store the messages
    int n; // The number of bytes received or sent

    // Create a socket for the client
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        // If an error occurs, print an error message and exit the program
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the server address parameters
    server_addr.sin_family = AF_INET; // The address family is IPv4
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // The server IP address is localhost
    server_addr.sin_port = htons(PORT); // The port number is converted to network byte order

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        // If an error occurs, print an error message and exit the program
        perror("Socket connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server at %s:%d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

    // Loop until the user enters "exit"
    while (1) {
        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));

        // Prompt the user to enter a message
        printf("Enter a message: ");
        fgets(buffer, sizeof(buffer), stdin);

        // Remove the newline character from the input
        buffer[strcspn(buffer, "\n")] = 0;

        // Check if the user wants to exit
        if (strcmp(buffer, "exit") == 0) {
            // Close the socket and exit the loop
            close(sock);
            break;
        }

        // Send the message to the server
        n = write(sock, buffer, strlen(buffer));
        if (n <= 0) {
            // If no bytes are sent or an error occurs, print an error message and exit the program
            perror("Socket writing failed");
            exit(EXIT_FAILURE);
        }

        // Print the sent message
        printf("Sent to server: %s\n", buffer);

        // Clear the buffer
        memset(buffer, 0, sizeof(buffer));

        // Receive a message from the server
        n = read(sock, buffer, sizeof(buffer));
        if (n <= 0) {
            // If no bytes are received or an error occurs, print an error message and exit the program
            perror("Socket reading failed");
            exit(EXIT_FAILURE);
        }

        // Print the received message
        printf("Received from server: %s\n", buffer);
    }

    return 0;
}
