/*6. Accept two numbers and operator (+, -, *, /) as command line arguments. Perform numerical operation as per operator in the child and display the result.*/

#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
        double n1, n2, ans;
        char op;

        printf("First number: ");
        scanf("%lf", &n1);
        printf("Operator: ");
        scanf(" %c", &op);
        printf("Second number: ");
        scanf("%lf", &n2);

        pid_t pid = fork();

        if(pid==0)
        {
                switch(op)
                {
                        case '+': ans = n1 + n2; break;
                        case '-': ans = n1 - n2; break;
                        case '*': ans = n1 * n2; break;
                        case '/': ans = n1 / n2; break;
                        default: printf("Invalid!"); break;
                }
                printf("Answer: %f\n", ans);
        }
        else
                wait(NULL);
}
