//6. Write a program using pipe to accept a string and pass it to child. Child will check the string whether it is palindrome or not. If palindrome then return message PALLINDROME otherwise NOT PALLINDROME to Parent.

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>

int main()
{
        int fd1[2], fd2[2];
        char str[50], result[20];

        pipe(fd1); pipe(fd2);

        if(fork() > 0)
        {
                close(fd1[0]);
                close(fd2[1]);

                printf("Enter a string: ");
                scanf("%s", str);

                write(fd1[1], str, strlen(str) + 1);
                close(fd1[1]);

                read(fd2[0], result, sizeof(result));
                close(fd2[0]);

                printf("Parent: %s\n", result);
        }
        else
        {
                close(fd1[1]);
                close(fd2[0]);

                read(fd1[0], str, sizeof(str));
                close(fd1[0]);
                int length = strlen(str);
                int isPalin = 1;

                for(int i=0; i<length/2; i++)
                {
                        if(tolower(str[i]) != tolower(str[length - i - 1]))
                        {
                                isPalin = 0;
                                break;
                        }
                }

                if(isPalin)
                {
                        strcpy(result, "PALINDROME");
                }
                else
                {
                        strcpy(result, "NOT PALINDROME");
                }

                write(fd2[1], result, strlen(result) + 1);
                close(fd2[1]);
        }
}
