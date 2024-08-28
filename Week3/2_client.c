#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100
#define FIFO_NAME "auth_fifo"

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char buffer[MAX_USERNAME_LEN + MAX_PASSWORD_LEN + 2];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    int fd = open(FIFO_NAME, O_WRONLY); 

    snprintf(buffer, sizeof(buffer), "%s %s", username, password);
    write(fd, buffer, strlen(buffer) + 1); 

    close(fd);
}
