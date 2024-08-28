/* 3.Write a client server program using message queue to cypher the text. Client take input a line of text from the user and sends to server using message Queue. Server reads text from the message queue and cypher the text (cypher method- simple one any of your choice) and return cyphered text to Client for display.*/

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

void cypher(char *text) {
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = 'z' - (text[i] - 'a');
        else if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = 'Z' - (text[i] - 'A');
    }
}

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    cypher(message.text);
    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
}
