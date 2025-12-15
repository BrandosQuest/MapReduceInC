#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include "LinkedListImplementation.c"
#include <wctype.h>
//#include "ReadFileReturnArrayOfWords.c"

#define NUM_THREADS 5
typedef struct KeyVal KeyVal;
struct KeyVal {
    void* key;
    void* val;
};
// 2. The "Envelope" struct to pass arguments to threads
typedef struct {
    int thread_id;
    Node* startNode;   // Where this thread starts counting
    Node* endNode;     // Where this thread stops (exclusive)
    int numNodesToEvaluate;
    //char* target_word;  // The word we are counting
    Node* combineOutputListTail;    // The Result: Map phase output
} ThreadArgs;

// 3. The Thread Function (The "Map" Phase)
// This logic runs on each CPU thread independently
void* func(void* arguments) {
    //printf("Thread number %d is working!\n", (int) pthread_self());
    ThreadArgs* args = (ThreadArgs*) arguments;
    printf("Thread number %d is working!\n", args->thread_id);
}

int main() {
    clock_t tic = clock();

    Node* tail = createList();
    Node* head = tail;
    FILE *f = fopen("input.txt", "r");

    char buf[256];
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
        //printf("%s\n", buf);
        //fflush(stdout);
    }
    //printList(tail);

    // --- STEP 1: PREPARE THREADS ---
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS]; // An array of "envelopes"
    int segmentSize = head->index / NUM_THREADS;
    Node* segmentStart = tail;

    // --- STEP 2: SPLIT THE LIST & LAUNCH ---
    // for each thread
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i+44;//initialize the thread id
        args[i].startNode = segmentStart;//initialize the first node of the portion of the list to analize

        // Find the end node or the num of nodes to evaluete for this segment
        // We traverse 'segment_size' steps forward
        Node* segmentEnd = segmentStart;
        for (int j = 0; j < segmentSize && segmentEnd != NULL; j++) {
            segmentEnd = segmentEnd->next;
        }

        args[i].endNode = segmentEnd;
        args[i].numNodesToEvaluate = segmentSize;
        /*// If this is the last thread, let it go to NULL (finish the list)
        if (i == NUM_THREADS - 1) {
            args[i].end_node = NULL;
        } else {
            args[i].endNode = segmentEnd;
            args[i].numNodesToEvaluate = segmentSize;
        }*/

        // Launch the thread!
        // We pass the address of the specific struct for this thread (&args[i])
        pthread_create(&threads[i], NULL, (void*)func, (void*)&args[i]);

        // Move the start pointer for the NEXT iteration
        segmentStart = segmentEnd;
    }
    printf("In main: All threads are created.\n");
    // --- STEP 3: REDUCE PHASE (Join and Aggregate) ---
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for thread to finish
         // Aggregate result
    }
    printf("In main: All threads have terminated.\n");

    // (Optional) Cleanup memory here...

    freeList(tail);
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}
/*#define NUM_THREADS 5

void* perform_work(void* arguments){
    int index = *((int*)arguments);
    int sleep_time = 1 + rand() % NUM_THREADS;
    printf("Thread %d: Started.\n", index);
    printf("Thread %d: Will be sleeping for %d seconds.\n", index, sleep_time);
    sleep(sleep_time);
    printf("Thread %d: Ended.\n", index);
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int result_code;

    //create all threads one by one
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("In main: Creating thread %d.\n", i);
        thread_args[i] = i;
        result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        assert(!result_code);
    }

    printf("In main: All threads are created.\n");

    // wait for each thread to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        result_code = pthread_join(threads[i], NULL);
        assert(!result_code);
        printf("In main: Thread %d has ended.\n", i);
    }

    printf("Main program has ended.\n");
    return 0;
}*/