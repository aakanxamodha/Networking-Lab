#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

void identify_class_and_mask(char *ip, char *class, char *mask) {
    unsigned int first_octet;
    sscanf(ip, "%u", &first_octet);

    if (first_octet >= 1 && first_octet <= 126) {
        strcpy(class, "Class A");
        strcpy(mask, "255.0.0.0");
    } else if (first_octet >= 128 && first_octet <= 191) {
        strcpy(class, "Class B");
        strcpy(mask, "255.255.0.0");
    } else if (first_octet >= 192 && first_octet <= 223) {
        strcpy(class, "Class C");
        strcpy(mask, "255.255.255.0");
    } else if (first_octet >= 224 && first_octet <= 239) {
        strcpy(class, "Class D");
        strcpy(mask, "Reserved for Multicast");
    } else {
        strcpy(class, "Class E");
        strcpy(mask, "Reserved for Experimental");
    }
}

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
        printf("Received IP address: %s\n", buffer);
        
        char class[20], mask[20];
        identify_class_and_mask(buffer, class, mask);
        
        char result[MAXLINE];
        snprintf(result, sizeof(result), "IP Class: %s, Default Mask: %s", class, mask);
        sendto(sockfd, result, strlen(result), 0, (struct sockaddr *) &clientAddr, addr_len);
    }
    
    close(sockfd);
    return 0;
}
