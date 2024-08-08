/*3. Write a program using pipe to accept an array of integers at parent and pass it to child. Child will pick only even numbers and return array of even numbers to parent.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
        int fd[2];
        pid_t pid;
        int arr[10];
        int size;

        printf("Size of array: ");
        scanf("%d", &size);

        printf("Array elements: ");
        for(int i=0; i<size; i++)
                scanf("%d", &arr[i]);

        pipe(fd);

        pid = fork();
        if(pid == 0)
        {
                close(fd[1]);
                read(fd[0], arr, sizeof(int) * size);
                close(fd[0]);

                printf("Even numbers: ");
                for(int i=0; i<size; i++)
                {
                        if(arr[i] % 2 == 0)
                        {
                                printf("%d ", arr[i]);
                        }
                }
                printf("\n");
        }
        else
        {
                close(fd[0]);
                write(fd[1], arr, sizeof(int) * size);
                close(fd[1]);

                wait(NULL);
        }
}
