/*4. Write a program to accept an array before forking and search the array in child for an element accepted and display the result.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
        pid_t pid;
        int find, found=0;

        int a[] = {1,2,3,4,5,6,7,8,9,10};
        int a_size = sizeof(a)/sizeof(a[0]);

        printf("Element to search: ");
        scanf("%d", &find);

        pid = fork();

        if(pid==0)
        {
                for(int i=0; i<a_size; i++)
                {
                        if(a[i] == find)
                        {
                                found = 1;
                                break;
                        }
                }

                if(found)
                {
                        printf("Found in array: %d\n", find);
                }
                else
                {
                        printf("Not found in array: %d\n", find);
                }
        }
        else
                wait(NULL);
}
