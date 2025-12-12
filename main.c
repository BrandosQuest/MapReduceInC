#include <pthread.h>
#include <stdio.h>
#include <stdint.h>


void* foo(void* arg) {
    printf("Created a new thread");
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


    return 0;
}
