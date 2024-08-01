/*7. Write a program to accept an integer before forking and child has to generate multiplication table corresponding to the integer.*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
        int num;
        pid_t pid;

        printf("Integer: ");
        scanf("%d", &num);

        pid = fork();

        if(pid==0)
        {
                printf("Child creating table= %d\n",num);
                for(int i=1; i<=10; i++)
                {
                        printf("%d x %d = %d\n", num, i, num * i);
                }
        }
        else
                wait(NULL);
}
