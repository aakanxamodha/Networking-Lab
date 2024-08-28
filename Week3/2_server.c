/* 2. Write client-server program using named pipes. Client accepts Username, password from user and passes them to server for authentication. Server has pre-stored username and passwords and it compares username and passwords and returns message -Welcome <username> or Login Access denied. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100
#define FIFO_NAME "auth_fifo"

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char stored_username[] = "user";
    char stored_password[] = "pass";
    char buffer[MAX_USERNAME_LEN + MAX_PASSWORD_LEN + 2];

    mkfifo(FIFO_NAME, 0666); 

    int fd = open(FIFO_NAME, O_RDONLY); 

    read(fd, buffer, sizeof(buffer));  
    sscanf(buffer, "%s %s", username, password);

    if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
        printf("Welcome %s\n", username);
    } else {
        printf("Login Access Denied\n");
    }

    close(fd);
    unlink(FIFO_NAME); 
}
