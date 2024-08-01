/*5. Write a program to write some characters to a file and close it in the parent. Child should open the same file in child and display.**/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/wait.h>

int main()
{
        int fd;
        pid_t pid;
        char buff[25];

        fd = open("F1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        write(fd, "Parent process\n", 15);
        close(fd);

        pid = fork();

        if(pid==0)
        {
                fd = open("F1.txt", O_RDONLY);
                int n;
                while((n = read(fd, buff, sizeof(buff) - 1)) > 0)
                {
                        buff[n] = '\0';
                        write(STDOUT_FILENO, buff, n);
                }
                close(fd);
        }
        else
                wait(NULL);
}
