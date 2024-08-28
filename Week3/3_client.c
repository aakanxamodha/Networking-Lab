/* 3.Write client-server program using named pipes. Client accepts Deposit amount and tenure (in years) and passes to server. Server has pre-stored information about different interest rates for different tenures. Accordingly, server applies appropriate interest rate and returns maturity amount and interest earned back to client.
0-12 months 5% 
13-24 months 6%
25-36 months 7%
>36 months 8% */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PIPE_NAME "/tmp/deposit_pipe"

int main() {
    int fd;
    float deposit, maturity_amount, interest_earned;
    int tenure;

    printf("Enter deposit amount: ");
    scanf("%f", &deposit);
    printf("Enter tenure (in years): ");
    scanf("%d", &tenure);

    fd = open(PIPE_NAME, O_WRONLY);
    write(fd, &deposit, sizeof(float));
    write(fd, &tenure, sizeof(int));
    close(fd);

    fd = open(PIPE_NAME, O_RDONLY);
    read(fd, &maturity_amount, sizeof(float));
    read(fd, &interest_earned, sizeof(float));
    close(fd);

    printf("Maturity Amount: %.2f\n", maturity_amount);
    printf("Interest Earned: %.2f\n", interest_earned);

    return 0;
}
