#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include "ReadFileReturnArrayOfWords.c"


void* foo(void* arg) {
    printf("Created a new thread\n");
    return NULL;
}

int main() {
    // Create a pthread_t variable to store
    // thread ID
    pthread_t thread1;
    // Creating a new thread.
    pthread_create(&thread1, NULL, foo, NULL);
    // WAIT for the thread to finish before exiting main
    pthread_join(thread1, NULL);


    Node* tail = createList();
    Node* head = tail;

    FILE *f = fopen("input.txt", "r");

    char buf[128];

    while( fscanf(f, "%s", buf) != EOF )
    {
        for (int i=0; buf[i] != 0; i++)
        {
            if (!iswalpha(buf[ i ]) && !iswdigit(buf[ i ]))
            {
                buf[i] = 0;
            }
        }
        if (buf[0]!=0) head = addNode(head, strdup(buf));
        //printf("%s\n", &buf);
    }
    printList(tail);
    freeList(tail);

    return 0;
}
