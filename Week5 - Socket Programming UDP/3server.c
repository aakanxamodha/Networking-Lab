#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MIN_BALANCE 1000

// Predefined account details (Account Number, PIN, Balance)
int accounts[5][3] = { 
    {1001, 1234, 5000},
    {1002, 2345, 3000},
    {1003, 3456, 7000},
    {1004, 4567, 1000},
    {1005, 5678, 2000}
};

// Function to process the transaction
void process_transaction(char *input, char *response) {
    int acc_num, pin, withdraw_amount;
    
    // Parse the client input (account number, pin, withdrawal amount)
    sscanf(input, "%d %d %d", &acc_num, &pin, &withdraw_amount);

    // Loop through stored accounts to find a match
    for (int i = 0; i < 5; i++) {
        if (accounts[i][0] == acc_num && accounts[i][1] == pin) {
            // Check if balance is enough after maintaining minimum balance
            if (accounts[i][2] - withdraw_amount >= MIN_BALANCE) {
                accounts[i][2] -= withdraw_amount; // Deduct the amount
                sprintf(response, "Withdrawal successful. New balance: %d\n", accounts[i][2]);
            } else {
                strcpy(response, "Not enough balance.\n");
            }
            return;
        }
    }
    // If account number or PIN is invalid
    strcpy(response, "Invalid Account Number or PIN.\n");
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the specified PORT and IP address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept a connection from the client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Read client data (account number, PIN, and withdrawal amount)
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    // Process the transaction and prepare the response
    process_transaction(buffer, response);

    // Send response back to the client
    send(new_socket, response, strlen(response), 0);

    // Close the connection
    close(new_socket);
    close(server_fd);
    return 0;
}
