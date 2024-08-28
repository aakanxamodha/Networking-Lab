/*FIFO(Named Pipe)
1. Write client-server program using named pipes. Client accepts a string and passes to Server through a named pipe and server checks the string for palindrome and returns a message - YES or NO to Client.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO_NAME "myfifo"

int main()
{
        char buffer[50];
        int fd;

        mkfifo(FIFO_NAME, 0666);
        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, buffer, sizeof(buffer));
        close(fd);

        buffer[strcspn(buffer, "\n")] = '\0';

        int len = strlen(buffer);
        int isPalin = 1;
        for(int i=0; i<len/2; i++)
        {
                if(buffer[i] != buffer[len-i-1])
                {
                        isPalin = 0;
                        break;
                }
        }
        fd = open(FIFO_NAME, O_WRONLY);
        if(isPalin)
        {
                write(fd, "YES", 4);
        }
        else
        {
                write(fd, "NO", 3);
        }
        close(fd);

        unlink(FIFO_NAME);
}
