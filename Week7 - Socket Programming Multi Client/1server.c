#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, client_socket[MAX_CLIENTS], max_clients = MAX_CLIENTS;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    fd_set readfds;
    char buffer[BUFFER_SIZE];
    int max_sd, sd, activity, i, valread;

    // Initialize all client_socket[] to 0 so they are not checked
    for (i = 0; i < max_clients; i++) {
        client_socket[i] = 0;
    }

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the server address to allow connections
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the server socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Clear the socket set and add the server socket to it
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        // Add the active client sockets to the set
        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            // If the socket is valid, add to the read list
            if (sd > 0)
                FD_SET(sd, &readfds);

            // Track the highest file descriptor number for select
            if (sd > max_sd)
                max_sd = sd;
        }

        // Wait for activity on one of the sockets, blocking indefinitely
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("Select error");
        }

        // Check if there's an incoming connection on the server socket
        if (FD_ISSET(server_fd, &readfds)) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }

            printf("New connection: socket fd is %d, IP is %s, port %d\n", 
                   new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Add the new socket to the client socket list
            for (i = 0; i < max_clients; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Added to client list as socket %d\n", i);
                    break;
                }
            }
        }

        // Handle input from the clients
        for (i = 0; i < max_clients; i++) {
            sd = client_socket[i];

            // Check if the client has sent data
            if (FD_ISSET(sd, &readfds)) {
                if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0) {
                    // Client has disconnected
                    getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    printf("Client disconnected: IP %s, port %d\n",
                           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                    // Close the socket and mark as 0 for reuse
                    close(sd);
                    client_socket[i] = 0;
                } else {
                    // Echo the message back to all other clients
                    buffer[valread] = '\0';
                    printf("Client %d sent: %s\n", i, buffer);

                    for (int j = 0; j < max_clients; j++) {
                        if (client_socket[j] != 0 && client_socket[j] != sd) {
                            send(client_socket[j], buffer, strlen(buffer), 0);
                        }
                    }
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
