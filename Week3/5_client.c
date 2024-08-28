#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char name[20], source[20], destination[20];
    int numSeats;
    char buffer[100];

    printf("Enter Name: ");
    scanf("%s", name);
    printf("Enter Source: ");
    scanf("%s", source);
    printf("Enter Destination: ");
    scanf("%s", destination);
    printf("Enter Number of Seats: ");
    scanf("%d", &numSeats);

    sprintf(buffer, "%s %s %s %d", name, source, destination, numSeats);

    int fd = open("/tmp/fifo", O_WRONLY);
    write(fd, buffer, strlen(buffer) + 1);
    close(fd);

    fd = open("/tmp/fifo", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    printf("%s\n", buffer);
    close(fd);

    return 0;
}
