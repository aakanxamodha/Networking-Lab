//2. Write a program using pipe to accept integer at parent and pass it to child. Child should check that number is Armstrong number or not and accordingly send a message - YES or NO to parent.

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

int main()
{
        int fd1[2], fd2[2], num;
        char result[4];

        pipe(fd1); pipe(fd2);

        if(fork() > 0)
        {
                close(fd1[0]);
                close(fd2[1]);

                printf("Parent: Enter an integer: ");
                scanf("%d", &num);

                write(fd1[1], &num, sizeof(num));
                close(fd1[1]);

                read(fd2[0], result, sizeof(result));
                close(fd2[0]);

                printf("Parent: Received from child: %s\n", result);
        }
        else
        {
                close(fd1[1]);
                close(fd2[0]);

                read(fd1[0], &num, sizeof(num));
                close(fd1[0]);

                int originalNum = num, remainder, n=0;
                float sum = 0.0;

                while(originalNum != 0)
                {
                        originalNum /= 10;
                        n++;
                }

                originalNum = num;

                while(originalNum != 0)
                {
                        remainder = originalNum % 10;
                        sum += pow(remainder, n);
                        originalNum /= 10;
                }

                if((int)sum == num)
                {
                        strcpy(result, "YES");
                }
                else
                {
                        strcpy(result, "NO");
                }

                write(fd2[1], result, sizeof(result));
                close(fd2[1]);
        }
}
