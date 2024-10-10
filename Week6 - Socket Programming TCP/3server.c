#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);
    
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));
    
    // Server information
    serverAddr.sin_family = AF_INET;  // IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    
    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        int n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *) &clientAddr, &addr_len);
        buffer[n] = '\0';
        printf("Client requested file: %s\n", buffer);
        
        FILE *file = fopen(buffer, "r");
        if (file == NULL) {
            sendto(sockfd, "file-not-found", strlen("file-not-found"), 0, (struct sockaddr *) &clientAddr, addr_len);
        } else {
            char chunk[11];
            while (fgets(chunk, 11, file) != NULL) {
                sendto(sockfd, chunk, strlen(chunk), 0, (struct sockaddr *) &clientAddr, addr_len);
            }
            sendto(sockfd, "end-of-file", strlen("end-of-file"), 0, (struct sockaddr *) &clientAddr, addr_len);
            fclose(file);
        }
    }
    
    close(sockfd);
    return 0;
}
