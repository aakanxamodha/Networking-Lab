/*5. Write a program using pipe to accept a matrix on n X n and pass it to child. Child will multiply each element of user’s choice to each element return new matrix back to parent.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
        int fd[2];
        pid_t pid;
        int m[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
        int n=3, multiply=2;
        int buffer[9];

        pipe(fd);

        pid = fork();
        if(pid == 0)
        {
                close(fd[1]);
                read(fd[0], buffer, sizeof(buffer));
                close(fd[0]);

                int ans[3][3], index=0;

                for(int i=0; i<n; i++)
                {
                        for(int j=0; j<n; j++)
                        {
                                ans[i][j] = buffer[index++];
                        }
                }

                for(int i=0; i<n; i++)
                {
                        for(int j=0; j<n; j++)
                        {
                                ans[i][j] *= multiply;
                                printf("%d ", ans[i][j]);
                        }
                        printf("\n");
                }
        }
        else
        {
                close(fd[0]);
                int index = 0;

                for(int i=0; i<n; i++)
                {
                        for(int j=0; j<n; j++)
                        {
                                buffer[index++] = m[i][j];
                        }
                }

                write(fd[1], buffer, sizeof(buffer));
                close(fd[1]);

                wait(NULL);
        }
}
