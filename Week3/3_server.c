#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

#define PIPE_NAME "/tmp/deposit_pipe"

int main() {
    int fd;
    float deposit, maturity_amount, interest_rate, interest_earned;
    int tenure;

    mkfifo(PIPE_NAME, 0666);

    fd = open(PIPE_NAME, O_RDONLY);
    read(fd, &deposit, sizeof(float));
    read(fd, &tenure, sizeof(int));

    if (tenure <= 1) {
        interest_rate = 0.05;
    } else if (tenure <= 2) {
        interest_rate = 0.06;
    } else if (tenure <= 3) {
        interest_rate = 0.07;
    } else {
        interest_rate = 0.08;
    }

    interest_earned = deposit * interest_rate * tenure;
    maturity_amount = deposit + interest_earned;

    close(fd);

    fd = open(PIPE_NAME, O_WRONLY);
    write(fd, &maturity_amount, sizeof(float));
    write(fd, &interest_earned, sizeof(float));

    close(fd);
    unlink(PIPE_NAME);

    return 0;
}
