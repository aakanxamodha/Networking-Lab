/* 4.Write client-server program using named pipes. Client accepts - electricity customer number and number of units consumed.
Server calculates the bill by applying different rate for different slabs of units consumed.
0- 50 units @ 1/- per unit.
51-100 units @1.5/- per unit.
101-200 units @ 2/- per unit.
>200 units @ 3/- per unit
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char *fifo = "/tmp/myfifo";
    mkfifo(fifo, 0666);

    char customer_number[10], units[10];
    printf("Enter Customer Number: ");
    scanf("%s", customer_number);
    printf("Enter Units Consumed: ");
    scanf("%s", units);

    fd = open(fifo, O_WRONLY);
    write(fd, customer_number, sizeof(customer_number));
    write(fd, units, sizeof(units));
    close(fd);

    char bill[100];
    fd = open(fifo, O_RDONLY);
    read(fd, bill, sizeof(bill));
    printf("Electricity Bill: %s\n", bill);
    close(fd);
    unlink(fifo);
    return 0;
}
