#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // Create client socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary format
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/Address not supported\n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed\n");
        return -1;
    }

    printf("Connected to the server. Type messages and press Enter to send.\n");

    while (1) {
        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Get input from the user
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send the message to the server
        send(sock, buffer, strlen(buffer), 0);

        // Exit the loop if the user types "exit"
        if (strcmp(buffer, "exit\n") == 0) {
            printf("Exiting the chat...\n");
            break;
        }

        // Read the server's response
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Server: %s\n", buffer);
        }
    }

    // Close the socket
    close(sock);
    return 0;
}
