#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Function to find IP class and related info
void process_ip(char *ip, char *response) {
    unsigned int first_octet;
    sscanf(ip, "%u", &first_octet);

    char class;
    char mask[16];
    char network[16];
    char broadcast[16];

    if (first_octet <= 127) {
        class = 'A';
        strcpy(mask, "255.0.0.0");
        sprintf(network, "%u.0.0.0", first_octet);
        sprintf(broadcast, "%u.255.255.255", first_octet);
    } else if (first_octet <= 191) {
        class = 'B';
        strcpy(mask, "255.255.0.0");
        sprintf(network, "%u.%u.0.0", first_octet, 0);
        sprintf(broadcast, "%u.%u.255.255", first_octet, 255);
    } else if (first_octet <= 223) {
        class = 'C';
        strcpy(mask, "255.255.255.0");
        sprintf(network, "%u.%u.%u.0", first_octet, 0, 0);
        sprintf(broadcast, "%u.%u.%u.255", first_octet, 0, 0);
    } else if (first_octet <= 239) {
        class = 'D';
        strcpy(mask, "Not applicable");
        sprintf(network, "Multicast");
        sprintf(broadcast, "N/A");
    } else {
        class = 'E';
        strcpy(mask, "Not applicable");
        sprintf(network, "Experimental");
        sprintf(broadcast, "N/A");
    }

    sprintf(response, "Class: %c\nMask: %s\nNetwork: %s\nBroadcast: %s\n", class, mask, network, broadcast);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, BUFFER_SIZE);
    printf("Received IP address: %s\n", buffer);

    process_ip(buffer, response);
    send(new_socket, response, strlen(response), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
