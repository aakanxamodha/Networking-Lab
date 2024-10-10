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
    struct sockaddr_in serverAddr;
    
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&serverAddr, 0, sizeof(serverAddr));
    
    // Server information
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    // Accept IP address from the user
    printf("Enter IP address: ");
    fgets(buffer, MAXLINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character
    
    sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    int n = recvfrom(sockfd, buffer, MAXLINE, 0, NULL, NULL);
    buffer[n] = '\0';
    printf("Server response: %s\n", buffer);
    
    close(sockfd);
    return 0;
}
