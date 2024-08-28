/* Message Queue 
1.Write a client server program using message queue to sort array of elements. Client takes input from user a set of integers and send to server using message queue for sorting. The server reads message queue and return sorted array to client for displaying at client. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 100

struct msg_buffer {
    long msg_type;
    int arr[MAX];
    int size;
} message;

void sort(int arr[], int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message), 1, 0);

    sort(message.arr, message.size);

    message.msg_type = 1;
    msgsnd(msgid, &message, sizeof(message), 0);
}
