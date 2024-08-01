/*6. Write a program to accept an array before forking and sort the array in child and display.*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

void sort(int a[], int n)
{
        int i, j, temp;
        for(i=0; i<n-1; i++)
        {
                for(j=0; j<n-i-1; j++)
                {
                        if(a[j] > a[j+1])
                        {
                                temp=a[j];
                                a[j]=a[j+1];
                                a[j+1]=temp;
                        }
                }
        }
}
int main()
{
        int n, i;
        printf("Number of array elements: ");
        scanf("%d",&n);

        int a[n];
        printf("Array elements: ");
        for(int i=0;  i<n; i++)
        {
                scanf("%d", &a[i]);
        }

        pid_t pid = fork();

        if(pid==0)
        {
                sort(a, n);
                printf("Sorted array: ");
                for(int i=0; i<n; i++)
                {
                        printf("%d ", a[i]);
                }
                printf("\n");
        }
        else
                wait(NULL);
}
