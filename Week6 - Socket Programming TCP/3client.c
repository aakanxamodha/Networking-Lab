#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE], filename[MAXLINE];
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
    
    // Accept file name from the user
    printf("Enter file name to download: ");
    fgets(filename, MAXLINE, stdin);
    filename[strcspn(filename, "\n")] = '\0';  // Remove newline character
    
    sendto(sockfd, filename, strlen(filename), 0, (const struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    FILE *file = fopen("received_file.txt", "w");
    if (file == NULL) {
        perror("File creation failed");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        int n = recvfrom(sockfd, buffer, MAXLINE, 0, NULL, NULL);
        buffer[n] = '\0';
        
        if (strcmp(buffer, "file-not-found") == 0) {
            printf("File not found on server.\n");
            break;
        } else if (strcmp(buffer, "end-of-file") == 0) {
            printf("File transfer complete.\n");
            break;
        }
        
        fputs(buffer, file);
        printf("Received: %s\n", buffer);
    }
    
    fclose(file);
    close(sockfd);
    return 0;
}
