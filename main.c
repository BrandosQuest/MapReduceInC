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

#define NUM_THREADS 1

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
    Node* inputTailRef = inputTail;
    Node* nextOutputNodeTemp = 0;
    //cycle through the key values from the input from the map
    int nodesVisited=0;
    Node* temp;
    while (inputTail != NULL) {
        temp = inputTail->next;

        int founded=0;

        //cicle trough the key values containing the array of the values, first loop it is empty and skipped
        Node* tempTail=inputTailRef;
        Node* temp3;
        while (tempTail != NULL && nodesVisited!=0) {
            temp3 = tempTail->next;

            if (areTheKeysEqual(inputTail->contentPointer, tempTail->contentPointer))//the 2 key strings are equal
            {
                founded=1;
                //add the value to the array of values using the same list
                ((KeyVal*)tempTail->contentPointer)->val = addNode(((KeyVal*)tempTail->contentPointer)->val,
                                                                     ((KeyVal*)inputTail->contentPointer)->val);
                break;
            }
            tempTail = temp3;
        }

        if (!founded)
        {
            KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));//this represents the array to be created
            if (kv!=NULL)//put things in kv
            {
                kv->key = ((KeyVal*)inputTail->contentPointer)->key;
                Node* valueListTail = createList();//creating the aray of values
                Node* valueListHead = valueListTail;//creating the aray of values
                valueListHead=addNode(valueListHead, ((KeyVal*)inputTail->contentPointer)->val);
                kv->val = valueListHead;
            }
            if (nodesVisited==0)
            {
                inputTail->contentPointer=kv;
                nextOutputNodeTemp = inputTail->next;
                inputTail->next = NULL;
            }else
            {
                nextOutputNodeTemp->prev->next = nextOutputNodeTemp; //i relink the list
                nextOutputNodeTemp->contentPointer=kv;
                nextOutputNodeTemp = nextOutputNodeTemp->next;//i get the next node
                if (nextOutputNodeTemp!=NULL)nextOutputNodeTemp->prev->next = NULL;//
            }
            //remember to find a way to free this from the head
        }
        inputTail = temp;

        nodesVisited++;
    }
    /*// Node* outputTail = createList();
    // Node* outputTailRef = outputTail;
    Node* outputHead = inputTail;
    Node* inputTailRef = inputTail;
    //printListRealTail(inputTailRef);

    //cycle through the key values from the input from the map
    Node* temp;
    int wordsFound=1;
    while (inputTail != NULL) {
        temp = inputTail->next;
        inputTail->next=NULL;

        int founded=0;

        //cicle trough the key values containing the array of the values, first loop it is empty and skipped
        Node* tempTail=inputTailRef->next;
        Node* temp3;
        //inputTail->next=NULL;
        while (tempTail != NULL && wordsFound!=1) {
            temp3 = tempTail->next;

            if (areTheKeysEqual(inputTail->contentPointer, tempTail->contentPointer) && wordsFound!=1)//the 2 key strings are equal
            {
                founded=1;
                //printList(((KeyVal*)tempTail->contentPointer)->val);

                //add the value to the array of values using the same list
                ((KeyVal*)tempTail->contentPointer)->val = addNode(((KeyVal*)tempTail->contentPointer)->val,
                                                                     ((KeyVal*)inputTail->contentPointer)->val);
                printf("index: %d\n", ((Node*)((KeyVal*)tempTail->contentPointer)->val)->index);
                break;
            }

            //printListFromHead(((KeyVal*)tempTail->contentPointer)->val);

            tempTail = temp3;
        }
        printf("number of words analized: %d\n", wordsFound);
        printf("word already found and so just added to list(true false): %d\n", founded);
        wordsFound++;

        if (!founded)
        {
            printf("list of values created\n");
            KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));//this represents the array to be created
            if (kv!=NULL)//put things in kv
            {
                kv->key = ((KeyVal*)inputTail->contentPointer)->key;
                Node* valueListTail = createList();//creating the aray of values
                Node* valueListHead = valueListTail;//creating the aray of values
                valueListHead=addNode(valueListHead, ((KeyVal*)inputTail->contentPointer)->val);
                kv->val = valueListHead;
            }
            outputHead=addNode(outputHead, kv);
            if (outputHead == NULL) free(kv);
            //outputHead->next=NULL;
            //remember to find a way to free this from the head
        }
        inputTail = temp;
    }*/
    /*Node* outputTail = createList();
    Node* outputTailRef = outputTail;
    Node* outputHead = outputTail;

    //cycle through the key values from the input from the map
    Node* temp;
    //inputTail = inputTail->next;
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
                break;
            }
            outputTail = temp2;
        }
        if (!founded)
        {
            KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));//this represents the array to be created
            if (kv!=NULL)//put things in kv
            {
                kv->key = ((KeyVal*)inputTail->contentPointer)->key;
                Node* valueListTail = createList();//creating the aray of values
                Node* valueListHead = valueListTail;//creating the aray of values
                valueListHead=addNode(valueListHead, ((KeyVal*)inputTail->contentPointer)->val);
                kv->val = valueListHead;
            }
            outputHead=addNode(outputHead, kv);
            if (outputHead == NULL) free(kv);
            //remember to find a way to free this from the head
        }
        inputTail = temp;
    }*/
    //printListRealTail(inputTailRef);
    return inputTailRef;
}

Node* combine(Node* inputTail) {
    Node* inputTailRef = inputTail;
    //printListRealTail(inputTailRef);
    Node* temp;
    //inputTail= inputTail->next;
    while (inputTail != NULL) {
        temp = inputTail->next;
        //to do stuff
        int* numberOfWordFound=malloc(sizeof(int));
        if (numberOfWordFound!=NULL) *numberOfWordFound=((Node*)((KeyVal*)inputTail->contentPointer)->val)->index+1;
        //printf("numberOfWordFound: %d\n", *numberOfWordFound);
        //printListFromHead((Node*)((KeyVal*)inputTail->contentPointer)->val);
        //printf("Number of words found: %d\n", *numberOfWordFound);
        ((KeyVal*)inputTail->contentPointer)->val = numberOfWordFound;
        /*KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));
        if (kv!=NULL){
            kv->key = ((KeyVal*)inputTail->contentPointer)->key;
            kv->val = numberOfWordFound;
        }
        inputTail->contentPointer= kv;*/
        //outputHead=addNode(outputHead, kv);
        /*if (outputHead == NULL)
        {
            free(numberOfWordFound);
            free(kv);
        }*/

        inputTail = temp;
    }
    /*Node* outputTail = createList();
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
    }*/
    //freeList(inputTail);
    //printListRealTail(inputTailRef);
    return inputTailRef;
}

// 3. The Thread Function (The "Map" Phase)
// This logic runs on each CPU thread independently
void threadFunc(void* arguments) {
    ThreadArgs* args = (ThreadArgs*) arguments;// I cast the arguments to the ThreadArgs type
    //printf("In thread: Thread number %d is working!\n", args->thread_id);

    //int encounteredOnce=1;
    int* encounteredOnce=malloc(sizeof(int));
    *encounteredOnce = 1;
    Node* tailReference=args->startNode;
    //Node* tailReference=createList();
    //tailReference->next=args->startNode;
    //printListTrad(tailReference);

    for (int i = 0; i < args->numNodesToEvaluate; i++)
    {
        KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));//create a kv portion of memory
        kv->key=args->startNode->contentPointer; //the key is the word encountered
        kv->val=encounteredOnce;// the value is 1, "found"
        args->startNode->contentPointer=kv;
        //mapOutputListHead = addNode(mapOutputListHead, kv);
        //if it is the last loop the next node must be null
        if (i+1==args->numNodesToEvaluate)
        {
            //printf("%d\n", i);
            args->startNode->next=NULL;//TODO free all of the rest of the list
            break;
        }
        args->startNode=getNextNode(args->startNode);
    }
    //printListRealTail(tailReference);
    args->combineOutputListTail=combine(shuffle(tailReference));
    //printListRealTail(args->combineOutputListTail);
    //free(encounteredOnce);
    //old way of doing thinks it worked!
    /*Node* mapOutputListTail = createList();
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

    args->combineOutputListTail=combine(shuffle(mapOutputListTail));*/
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
    while (inputHead != NULL && inputHead->contentPointer != NULL) {
        temp = inputHead->prev;
        //do stuff
        sum = sum + *(int*)inputHead->contentPointer;
        inputHead = temp;
    }
    return sum;
}

Node* reduce(Node* inputTail) {
    /*Node* outputTail = createList();
    Node* outputHead = outputTail;

    Node* temp;
    //printList(inputTail);
    //inputTail= inputTail->next;
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
    return outputTail;*/
    //printf("reduce: output of shuffle\n");
    //printListRealTail(inputTail);
    Node* inputTailRef = inputTail;
    Node* temp;
    while (inputTail != NULL) {
        temp = inputTail->next;
        //to do stuff
        int* numberOfWordFound=malloc(sizeof(int));
        if (numberOfWordFound != NULL) *numberOfWordFound = sumContentOfListOfInt(
            (Node*)((KeyVal*)inputTail->contentPointer)->val);

        KeyVal* kv = (KeyVal*) calloc(1, sizeof(KeyVal));
        if (kv!=NULL){
            kv->key = ((KeyVal*)inputTail->contentPointer)->key;
            kv->val = numberOfWordFound;
        }

        ((KeyVal*)inputTail->contentPointer)->val = numberOfWordFound;

        inputTail = temp;
    }
    return inputTailRef;
}

int main() {
    clock_t tic = clock();

    Node* tail = createList();
    Node* head = tail;
    FILE *f = fopen("input.txt", "r");

    //The file is read, and split into words
    char buf[256];
    while( fscanf(f, "%255s", buf) != EOF )
    {
        for (int i=0; buf[i] != 0; i++)
        {
            if (!iswalpha(buf[ i ]) && !iswdigit(buf[ i ]))
            {
                buf[i] = 0;
            }
        }
        if (buf[0]!=0) head = addNode(head, strdup(buf));
    }
    //printListTrad(tail);
    // --- STEP 1: PREPARE THREADS ---
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS]; // An array of "envelopes"(used for passing things to the threads)
    int segmentSize = (head->index+1) / NUM_THREADS;//the theoretical size of a portion of list passed to the thread
    int reminder=(head->index+1) % NUM_THREADS;
    Node* segmentStart = tail->next;//the  tail's always null
    //printListTrad(segmentStart);

    // --- STEP 2: SPLIT THE LIST & LAUNCH ---
    // for each thread
    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i;//initialize the thread id
        args[i].startNode = segmentStart;//initialize the first node of the portion of the list to analyze

        // Find the end node or the num of nodes to evaluate for this segment
        // We traverse 'segment_size' steps forward
        Node* segmentEnd = segmentStart;
        int j;
        for (j = 0; j < segmentSize && segmentEnd != NULL; j++) {
            segmentEnd = segmentEnd->next;
            if (j+1 == segmentSize)//if this is the last loop
            {
                if (reminder>0)//if we have spare reminders to assign
                {
                    segmentEnd = segmentEnd->next; //assign a reminder
                    reminder--; //remove a reminder form the reminders
                    j++;
                }
            }
        }
        printf("In main: thread %d has %d nodes assigned to it\n", i, j);//print info about thread

        args[i].endNode = segmentEnd;//assign the endNode
        args[i].numNodesToEvaluate = j;//assign the number of nodes
        //TODO to decide if they are both necessary

        // Launch the thread!
        // We pass the address of the specific struct for this thread (&args[i])
        pthread_create(&threads[i], NULL, (void*)threadFunc, (void*)&args[i]);

        // Move the start pointer for the NEXT iteration
        segmentStart = segmentEnd;
    }
    printf("In main: All threads are created.\n");

    // --- STEP 3: REDUCE PHASE (Join and Aggregate) ---
    Node* nodesOutputTail = 0;
    Node* nodesOutputHead = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for thread to finish
        //printListTrad(args[i].combineOutputListTail);

        if (i==0)
        {
            nodesOutputTail=args[i].combineOutputListTail;
            nodesOutputHead = nodesOutputTail;
        } else
        {
            if (nodesOutputHead==NULL) break;
            args[i].combineOutputListTail->prev =  nodesOutputHead;
            nodesOutputHead->next = args[i].combineOutputListTail;
        }
        while (nodesOutputHead->next != NULL)
        {
            nodesOutputHead = nodesOutputHead->next;
        }
        //freeList(args[i].combineOutputListTail);
        //printf("In main: list from thread %d freed\n", i);
    }
    /*Node* nodesOutputTail = createList();
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
    }*/
    //printList(nodesOutputTail);
    //printListFromHead(nodesOutputHead);

    //nodesOutputTail= nodesOutputTail->prev;
    //printListRealTail(nodesOutputTail);
    printf("In main: final result\n");

    Node* finalResultsList=reduce(shuffle(nodesOutputTail));
    printListRealTail(finalResultsList);

    // Aggregate result
    printf("In main: All threads have terminated.\n\n");

    // (Optional) Cleanup memory here...

    freeList(tail);
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
}