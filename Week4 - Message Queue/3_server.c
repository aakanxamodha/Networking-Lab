/* 3.Write a client server program using message queue to cypher the text. Client take input a line of text from the user and sends to server using message Queue. Server reads text from the message queue and cypher the text (cypher method- simple one any of your choice) and return cyphered text to Client for display.*/

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
