/*2. Write a program to demonstrate the concept of parent & child processes using fork () system call in which the parent reads a file name from the keyboard and child process uses the file name and reads first 10 characters from the file.*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
        int fd,n;
        char buff[11], fname[20];

        printf("Enter file name: ");
        scanf("%s",  fname);

        pid_t pid;
        pid=fork();

        if(pid<0)
                printf("Fork failed");
        else
                if(pid==0)
                {
                        fd=open(fname,O_RDONLY);
                        n=read(fd,buff,10);

                        buff[n]='\0';
                        printf("First 10 characters: %s\n", buff);

                        close(fd);
                }
                else
                {
                        wait(NULL);
                }
}
