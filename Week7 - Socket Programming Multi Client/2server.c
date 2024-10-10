#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void classify_ip(const char *ip, char *class_type, char *default_mask) {
    unsigned char first_octet = atoi(strtok((char *)ip, "."));
    if (first_octet >= 1 && first_octet <= 126) {
        strcpy(class_type, "A");
        strcpy(default_mask, "255.0.0.0");
    } else if (first_octet >= 128 && first_octet <= 191) {
        strcpy(class_type, "B");
        strcpy(default_mask, "255.255.0.0");
    } else if (first_octet >= 192 && first_octet <= 223) {
        strcpy(class_type, "C");
        strcpy(default_mask, "255.255.255.0");
    } else if (first_octet >= 224 && first_octet <= 239) {
        strcpy(class_type, "D");
        strcpy(default_mask, "N/A");
    } else {
        strcpy(class_type, "E");
        strcpy(default_mask, "N/A");
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    char class_type[10], default_mask[20];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("New connection: socket fd is %d, ip is : %s , port : %d\n",
               new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        // Read IP from client
        read(new_socket, buffer, BUFFER_SIZE);
        printf("Received IP address: %s\n", buffer);
        
        // Classify IP
        classify_ip(buffer, class_type, default_mask);

        // Send back class and default mask
        snprintf(buffer, BUFFER_SIZE, "Class: %s, Default Mask: %s", class_type, default_mask);
        send(new_socket, buffer, strlen(buffer), 0);
        
        close(new_socket);
    }
    return 0;
}
