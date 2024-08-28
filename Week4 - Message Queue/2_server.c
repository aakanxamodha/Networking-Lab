/* 2.Write a client server program using message queue to simulate calculator operations (+, -, *, / between two numbers). Client accepts two numbers and operation to be performed from the user and writes to message queue. Server reads from message queue and performs the required operation to produce result. The server returns the result to client using message queue in order to display result.*/

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

    msgrcv(msgid, &message, sizeof(message), 1, 0);

    switch (message.op) {
        case '+':
            message.result = message.num1 + message.num2;
            break;
        case '-':
            message.result = message.num1 - message.num2;
            break;
        case '*':
            message.result = message.num1 * message.num2;
            break;
        case '/':
            if (message.num2 != 0)
                message.result = message.num1 / message.num2;
            else
                message.result = 0; // Handle division by zero
            break;
        default:
            printf("Invalid operator\n");
            exit(1);
    }

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
}
