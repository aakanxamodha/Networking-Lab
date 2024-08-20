//4. Write a program using pipe to accept details of a student such as - RegNo, Mark1, Mark2, Mark3 and send it to child. Child will find average and accordingly assign Grades (A+, A, B, C, D, E, F- assume some criteria) and return grade to Parent.

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
        int fd1[2], fd2[2], regNo, m1, m2, m3;
        float avg;
        char grade[3];

        pipe(fd1);
        pipe(fd2);

        if (fork() > 0)
        {
                close(fd1[0]);
                close(fd2[1]);

                printf("Enter registration number: ");
                scanf("%d", &regNo);
                printf("Enter Mark 1: ");
                scanf("%d", &m1);
                printf("Enter Mark 2: ");
                scanf("%d", &m2);
                printf("Enter Mark 3: ");
                scanf("%d", &m3);

                write(fd1[1], &regNo, sizeof(regNo));
                write(fd1[1], &m1, sizeof(m1));
                write(fd1[1], &m2, sizeof(m2));
                write(fd1[1], &m3, sizeof(m3));
                close(fd1[1]);

                read(fd2[0], grade, sizeof(grade));
                close(fd2[0]);

                printf("Parent: Student = %d, Grade = %s\n", regNo, grade);
           }
           else
           {
                close(fd1[1]);
                close(fd2[0]);

                read(fd1[0], &regNo, sizeof(regNo));
                read(fd1[0], &m1, sizeof(m1));
                read(fd1[0], &m2, sizeof(m2));
                read(fd1[0], &m3, sizeof(m3));
                close(fd1[0]);

                avg = (m1 + m2 + m3) / 3.0;

                if (avg >= 90)
                {
                        strcpy(grade, "A+");
                }
                else
                        if (avg >= 80)
                        {
                                strcpy(grade, "A");
                        }
                        else
                                if (avg >= 70)
                                {
                                        strcpy(grade, "B");
                                }
                                else
                                        if (avg >= 60)
                                        {
                                                strcpy(grade, "C");
                                        }
                                        else
                                                if (avg >= 50)
                                                {
                                                        strcpy(grade, "D");
                                                }
                                                else
                                                        if (avg >= 40)
                                                        {
                                                                strcpy(grade, "E");
                                                        }
                                                        else
                                                        {
                                                                strcpy(grade, "F");
                                                        }

        write(fd2[1], grade, sizeof(grade));
        close(fd2[1]);
    }
}
