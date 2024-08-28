#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char *fifo = "/tmp/myfifo";
    mkfifo(fifo, 0666);

    char customer_number[10], units[10];
    fd = open(fifo, O_RDONLY);
    read(fd, customer_number, sizeof(customer_number));
    read(fd, units, sizeof(units));
    close(fd);

    int units_consumed = atoi(units);
    float bill = 0;
    if (units_consumed <= 50)
        bill = units_consumed * 1.0;
    else if (units_consumed <= 100)
        bill = 50 + (units_consumed - 50) * 1.5;
    else if (units_consumed <= 200)
        bill = 50 + 75 + (units_consumed - 100) * 2.0;
    else
        bill = 50 + 75 + 200 + (units_consumed - 200) * 3.0;

    char result[100];
    snprintf(result, sizeof(result), "Customer No: %s, Units: %d, Bill: ₹%.2f", customer_number, units_consumed, bill);

    fd = open(fifo, O_WRONLY);
    write(fd, result, sizeof(result));
    close(fd);
    unlink(fifo);
    return 0;
}
