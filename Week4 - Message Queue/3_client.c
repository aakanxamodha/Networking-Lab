#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

struct msg_buffer {
    long msg_type;
    char text[MAX];
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Enter text to cypher: ");
    fgets(message.text, MAX, stdin);

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Cyphered text: %s\n", message.text);
    msgctl(msgid, IPC_RMID, NULL);
}
