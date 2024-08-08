/*1. Write a program using pipe to send a string from parent to child in order to print number of characters and digits in the string.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>

int main()
{
        int fd[2];
        pid_t pid;
        char str[] = "Aakanxa230970031";
        char buffer[50];

        pipe(fd);
        pid = fork();

        if(pid == 0)
        {
                close(fd[1]);
                read(fd[0], buffer, sizeof(buffer));
                close(fd[0]);

                int char_count = 0, digit_count = 0;
                for(int i=0; i<strlen(buffer); i++)
                {
                        if(isalpha(buffer[i])) char_count++;
                        if(isdigit(buffer[i])) digit_count++;
                }

                printf("Characters: %d, Digits: %d\n", char_count, digit_count);
        }
        else
        {
                close(fd[0]);
                write(fd[1], str, strlen(str) + 1);
                close(fd[1]);

                wait(NULL);
        }
}
