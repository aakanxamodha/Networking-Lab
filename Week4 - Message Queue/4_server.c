/* 4. Write a client server program using message queue to book multiplex tickets. Assume that there are 5 ticket categories and each category there are 20 tickets. Assume that this is pre-stored information and available at server. From client program, User inputs- Name, Phone no, Ticket category and Number of tickets and pass it to server for ticket reservation. Depending on users input, decrement the number of seats in corresponding category, send booking information to client for displaying on the screen. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define TICKETS_PER_CATEGORY 20

struct msg_buffer {
    long msg_type;
    char name[50];
    char phone[15];
    int category;
    int tickets;
    char response[100];
} message;

int available_tickets[5] = {TICKETS_PER_CATEGORY, TICKETS_PER_CATEGORY, TICKETS_PER_CATEGORY, TICKETS_PER_CATEGORY, TICKETS_PER_CATEGORY};

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message), 1, 0);

    if (message.category < 1 || message.category > 5) {
        strcpy(message.response, "Invalid ticket category.");
    } else if (available_tickets[message.category - 1] >= message.tickets) {
        available_tickets[message.category - 1] -= message.tickets;
        snprintf(message.response, sizeof(message.response), "Booking successful! %d tickets booked for %s.", message.tickets, message.name);
    } else {
        strcpy(message.response, "Not enough tickets available.");
    }

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
}
