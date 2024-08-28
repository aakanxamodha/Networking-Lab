#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

struct msg_buffer {
    long msg_type;
    int arr[MAX];
    int size;
} message;

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    printf("Enter the number of elements: ");
    scanf("%d", &message.size);

    printf("Enter the elements: ");
    for(int i = 0; i < message.size; i++) {
        scanf("%d", &message.arr[i]);
    }

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    printf("Sorted array: ");
    for(int i = 0; i < message.size; i++) {
        printf("%d ", message.arr[i]);
    }
    printf("\n");

    msgctl(msgid, IPC_RMID, NULL);
}
