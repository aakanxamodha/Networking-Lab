/* 5. Write client-server program using named pipes. Client accepts - passenger name, source, destination and number of seats and sends to server. Assume that server has pre-stored information about - Source, Destination, ticket_rate and number of seats available. On receival of information from client, server checks for availability of seats. If available, accordingly decrement seats and sends bill amount to client, otherwise display message to client that -Seats not available */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

struct TicketInfo {
    char source[20];
    char destination[20];
    int rate;
    int seats;
};

int main() {
    struct TicketInfo tickets[] = {
        {"CityA", "CityB", 500, 10},
        {"CityA", "CityC", 300, 5}
    };
    char buffer[100];
    int i, numSeats, bill;
    char source[20], destination[20], name[20];

    mkfifo("/tmp/fifo", 0666);
    
    int fd = open("/tmp/fifo", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    sscanf(buffer, "%s %s %s %d", name, source, destination, &numSeats);
    close(fd);

    int found = 0;
    for (i = 0; i < 2; i++) {
        if (strcmp(tickets[i].source, source) == 0 && strcmp(tickets[i].destination, destination) == 0) {
            found = 1;
            if (tickets[i].seats >= numSeats) {
                tickets[i].seats -= numSeats;
                bill = numSeats * tickets[i].rate;
                sprintf(buffer, "Seats booked. Total Bill: %d", bill);
            } else {
                strcpy(buffer, "Seats not available");
            }
            break;
        }
    }
    if (!found) strcpy(buffer, "Route not found");

    fd = open("/tmp/fifo", O_WRONLY);
    write(fd, buffer, strlen(buffer) + 1);
    close(fd);

    return 0;
}
