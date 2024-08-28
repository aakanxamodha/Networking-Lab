#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define FIFO_NAME "myfifo"

int main()
{
        char buffer[50];
        int fd;

        printf("Enter a string: ");
        scanf("%s", buffer);

        fd = open(FIFO_NAME, O_WRONLY);
        write(fd, buffer, strlen(buffer)+1);
        close(fd);

        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        close(fd);

        printf("Palindrome: %s\n", buffer);
}
