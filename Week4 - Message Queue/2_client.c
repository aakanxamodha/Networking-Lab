#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    int num1, num2;
    char op;
    int result;
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Enter first number: ");
    scanf("%d", &message.num1);
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &message.op);
    printf("Enter second number: ");
    scanf("%d", &message.num2);

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Result: %d\n", message.result);
    msgctl(msgid, IPC_RMID, NULL);
}
