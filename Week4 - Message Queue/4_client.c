#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char name[50];
    char phone[15];
    int category;
    int tickets;
    char response[100];
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Enter your name: ");
    scanf("%s", message.name);
    printf("Enter your phone number: ");
    scanf("%s", message.phone);
    printf("Enter ticket category (1-5): ");
    scanf("%d", &message.category);
    printf("Enter number of tickets: ");
    scanf("%d", &message.tickets);

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("%s\n", message.response);
    msgctl(msgid, IPC_RMID, NULL);
}
