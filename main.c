#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
typedef struct KeyVal KeyVal;
struct KeyVal {
    void* key;
    void* val;
};
#include "LinkedListImplementation.c"
#include <wctype.h>
//#include "ReadFileReturnArrayOfWords.c"

#define NUM_THREADS 2

// 2. The "Envelope" struct to pass arguments to threads
typedef struct {
    int thread_id;
    Node* startNode;   // Where this thread starts counting
    Node* endNode;     // Where this thread stops (exclusive)
    int numNodesToEvaluate;
    //char* target_word;  // The word we are counting
    Node* combineOutputListTail;    // The Result: Map phase output
} ThreadArgs;
//case sensitive
int areTheKeysEqual(KeyVal* k1, KeyVal* k2) {
    if (k2==NULL) return 0;
    //printf("string 1: %s\tstring 2: %s\t", (const char*)k1->key, (const char*)k2->key);
    //printf("string 1p: %p\tstring 2p: %p\n", (const char*)k1->key, (const char*)k2->key);
    fflush(stdout);

    int result=0;
    result=!strcmp((const char*)k1->key, (const char*)k2->key);
    //printf("Result: %d\n", result);
    fflush(stdout);
    return result;
}

//a shuffle func that takes the key value list and for each key that is equal it creates an array or list of the values
Node* shuffle(Node* inputTail) {
    Node* outputTail = createList();
    Node* outputTailRef = outputTail;
    Node* outputHead = outputTail;

    /*{Node* temp;
    inputTail = inputTail->next;
    int j=0;
    while (inputTail != NULL) {
        temp = inputTail->next;


        //do stuff
        printf("j: %d\n", j++);
        int founded=0;
        int i=0;
        outputTailTemp=outputTail;

        Node* temp2;
        outputTailTemp = outputTailTemp->next;
        while (outputTailTemp != NULL)
        {
            temp2 = outputTailTemp->next;
            //do stuff
            {
            printf("i: %d\n", i++);
            if (areTheKeysEqual(inputTail->contentPointer, outputTailTemp->contentPointer))
            {
                //do stuff
                //add to the outputlist the value from the imput list
                ((KeyVal*)outputTailTemp->contentPointer)->val = addNode(
                    ((KeyVal*)outputTailTemp->contentPointer)->val, ((KeyVal*)inputTail->contentPointer)->val);
                founded=1;
                printf("Match found for %s\n", (const char*)((KeyVal*)inputTail->contentPointer)->key);
                break;
            }
            printf("outputTailTemp pointer: %p\n", outputTailTemp);
            //if the keys are equal than add the value to the valueList on the specific outputlist value
            //else if there is no match create a new node on the outputlist with the same key and a list on the value containing the specific value
            }
            outputTailTemp = temp2;
        }
        if (!founded)
        {
            printf("Match not founded for %s\n", (const char*)((KeyVal*)inputTail->contentPointer)->key);
            KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));
            kv->key = ((KeyVal*)inputTail->contentPointer)->key;
            Node* valueListTail = createList();
            Node* valueListHead = valueListTail;
            valueListHead=addNode(valueListHead, ((KeyVal*)inputTail->contentPointer)->val);
            kv->val = valueListHead;
            printf("outputList content pointer: %p\n", kv);
            outputHead = addNode(outputHead, kv);
            //remember to find a way to free this from the head
        }


        inputTail = temp;
    }}*/

    //cicle trough the key values from the input from the map
    Node* temp;
    inputTail = inputTail->next;
    while (inputTail != NULL) {
        temp = inputTail->next;

        int founded=0;

        //cicle trough the key values containing the array of the values, first loop it is empty and skipped
        outputTail=outputTailRef;
        Node* temp2;
        outputTail = outputTail->next;
        while (outputTail != NULL)
        {
            temp2 = outputTail->next;
            // to do stuff printf("Content of list 1, 2: %d, %d\n", *(int*)Tail1->contentPointer, *(int*)Tail2->contentPointer);
            if (areTheKeysEqual(inputTail->contentPointer, outputTail->contentPointer))//the 2 key strings are equal
            {
                founded=1;
                //add the value to the array of values
                ((KeyVal*)outputTail->contentPointer)->val = addNode(((KeyVal*)outputTail->contentPointer)->val,
                                                                     ((KeyVal*)inputTail->contentPointer)->val);
                //if (((KeyVal*)outputTail->contentPointer)->val == NULL) free(j);
                /*int* j=malloc(sizeof(int));
                if (j!=NULL)*j = 1;

                ((KeyVal*)outputTail->contentPointer)->val = addNode(((KeyVal*)outputTail->contentPointer)->val, j);
                if (((KeyVal*)outputTail->contentPointer)->val == NULL) free(j);*/
                break;
            }
            outputTail = temp2;
        }
        if (!founded)
        {
            //int* j=malloc(sizeof(int));//this represents the array to be created
            KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));//this represents the array to be created
            if (kv!=NULL)//put things in kv
            {
                kv->key = ((KeyVal*)inputTail->contentPointer)->key;
                Node* valueListTail = createList();//creating the aray of values
                Node* valueListHead = valueListTail;//creating the aray of values
                valueListHead=addNode(valueListHead, ((KeyVal*)inputTail->contentPointer)->val);
                kv->val = valueListHead;
                //printf("outputList content pointer: %p\n", kv);
            }
            outputHead=addNode(outputHead, kv);
            if (outputHead == NULL) free(kv);
            //printf("Match not founded for %s\t created list of values\n", (const char*)((KeyVal*)inputTail->contentPointer)->key);
            //remember to find a way to free this from the head
        }

        inputTail = temp;
    }




    /*Node* temp3;
    outputTail = outputTailRef;
    outputTail= outputTail->next;
    while (outputTail != NULL && outputTail->contentPointer != 0) {
        temp3 = outputTail->next;
        printf("List of values\n");
        printListFromHead(((KeyVal*)outputTail->contentPointer)->val);
        outputTail = temp3;
    }*/

    return outputTailRef;
}

Node* combine(Node* inputTail) {
    Node* outputTail = createList();
    Node* outputHead = outputTail;

    Node* temp;
    inputTail= inputTail->next;
    while (inputTail != NULL) {
        temp = inputTail->next;
        //to do stuff
        int* numberOfWordFound=malloc(sizeof(int));
        if (numberOfWordFound!=NULL) *numberOfWordFound=((Node*)((KeyVal*)inputTail->contentPointer)->val)->index+1;
        //printf("Number of words found: %d\n", *numberOfWordFound);
        KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));
        if (kv!=NULL){
            kv->key = ((KeyVal*)inputTail->contentPointer)->key;
            kv->val = numberOfWordFound;
        }
        outputHead=addNode(outputHead, kv);
        if (outputHead == NULL)
        {
            free(numberOfWordFound);
            free(kv);
        }

        inputTail = temp;
    }
    //freeList(inputTail);
    return outputTail;
}

// 3. The Thread Function (The "Map" Phase)
// This logic runs on each CPU thread independently
void* threadFunc(void* arguments) {
    ThreadArgs* args = (ThreadArgs*) arguments;
    printf("In thread: Thread number %d is working!\n", args->thread_id);

    Node* mapOutputListTail = createList();
    Node* mapOutputListHead = mapOutputListTail;
    int encounteredOnce=1;

    for (int i = 0; i < args->numNodesToEvaluate; i++)
    {
        KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));
        kv->key=args->startNode->contentPointer;
        args->startNode=getNextNode(args->startNode);
        kv->val=&encounteredOnce;
        //printf("the pointer to the value is %p\n", kv->val);
        mapOutputListHead = addNode(mapOutputListHead, kv);
    }

    args->combineOutputListTail=combine(shuffle(mapOutputListTail));
    /*printList(mapOutputListTail);
    printf("mapOutputListTail \t%p\n", mapOutputListTail);
    printf("args->combineOutputListTail \t%p\n", args->combineOutputListTail);*/
    //printf("combineOutputListTail thread: %d\n", args->thread_id);
    //printList(args->combineOutputListTail);

    //still have to free a lot of lists
}
int sumContentOfListOfInt(Node* inputHead) {
    int sum=0;
    Node* temp;
    while (inputHead != NULL && inputHead->contentPointer != 0) {
        temp = inputHead->prev;
        //do stuff
        sum = sum + *(int*)inputHead->contentPointer;
        inputHead = temp;
    }
    return sum;
}

Node* reduce(Node* inputTail) {
    Node* outputTail = createList();
    Node* outputHead = outputTail;

    Node* temp;
    inputTail= inputTail->next;
    while (inputTail != NULL) {
        temp = inputTail->next;
        //to do stuff
        int* numberOfWordFound=malloc(sizeof(int));
        if (numberOfWordFound != NULL) *numberOfWordFound = sumContentOfListOfInt(
            (Node*)((KeyVal*)inputTail->contentPointer)->val);
        //printf("Number of words found: %d\n", *numberOfWordFound);
        KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));
        if (kv!=NULL){
            kv->key = ((KeyVal*)inputTail->contentPointer)->key;
            kv->val = numberOfWordFound;
        }
        outputHead=addNode(outputHead, kv);
        if (outputHead == NULL)
        {
            free(numberOfWordFound);
            free(kv);
        }

        inputTail = temp;
    }
    //freeList(inputTail);
    return outputTail;
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
    //printListTrad(tail);

    // --- STEP 1: PREPARE THREADS ---
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS]; // An array of "envelopes"
    int segmentSize = (head->index+1) / NUM_THREADS;
    int reminder=(head->index+1) % NUM_THREADS;
    Node* segmentStart = tail->next;

    // --- STEP 2: SPLIT THE LIST & LAUNCH ---
    // for each thread
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i;//initialize the thread id
        args[i].startNode = segmentStart;//initialize the first node of the portion of the list to analize

        // Find the end node or the num of nodes to evaluete for this segment
        // We traverse 'segment_size' steps forward
        Node* segmentEnd = segmentStart;
        int j;
        for (j = 0; j < segmentSize && segmentEnd != NULL; j++) {
            segmentEnd = segmentEnd->next;
            if (j+1 == segmentSize)
            {
                if (reminder>0)
                {
                    segmentEnd = segmentEnd->next;
                    reminder--;
                    j++;
                }
            }
        }
        printf("In main: thread %d has %d nodes assigned to it\n", i, j);
        //if (segmentEnd == NULL) break;

        args[i].endNode = segmentEnd;
        args[i].numNodesToEvaluate = j;

        // Launch the thread!
        // We pass the address of the specific struct for this thread (&args[i])
        pthread_create(&threads[i], NULL, (void*)threadFunc, (void*)&args[i]);

        // Move the start pointer for the NEXT iteration
        //if (segmentEnd->next == NULL) break;
        //segmentStart = segmentEnd->next;
        segmentStart = segmentEnd;
    }
    printf("In main: All threads are created.\n");
    // --- STEP 3: REDUCE PHASE (Join and Aggregate) ---
    Node* nodesOutputTail = createList();
    Node* nodesOutputHead = nodesOutputTail;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for thread to finish
        //printListTrad(args[i].combineOutputListTail);
        nodesOutputHead->next=args[i].combineOutputListTail->next;
        nodesOutputHead->next->prev = nodesOutputHead;
        while (nodesOutputHead->next != NULL)
        {
            nodesOutputHead = nodesOutputHead->next;
        }
        //freeList(args[i].combineOutputListTail);
        //printf("In main: list from thread %d freed\n", i);
    }
    printList(nodesOutputTail);
    printListFromHead(nodesOutputHead);

    printf("In main: final result\n");

    printList(reduce(shuffle(nodesOutputTail)));

    // Aggregate result
    printf("In main: All threads have terminated.\n\n");

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