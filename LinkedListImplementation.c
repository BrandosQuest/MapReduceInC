#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node {
    void* contentPointer;
    Node* next;
    Node* prev;
    int32_t index;
};


Node* createList() {
    Node* node = calloc(1, sizeof(Node));
    if (node == NULL) {
        perror("Failed to create list");
        exit(EXIT_FAILURE);
    }
    node->index=-1;
    return node;
}

//returns the new head from the previous tail, if only one node, returns the head from the tail
Node* addNode(Node* head, void* contentPointer) {
    Node* nodeJustCreated = calloc(1, sizeof(Node));
    if (nodeJustCreated == NULL) {
        return NULL; // Allocation failed
    }
    nodeJustCreated->contentPointer = contentPointer;
    nodeJustCreated->index = head->index+1;
    head->next = nodeJustCreated;
    nodeJustCreated->prev = head;
    return nodeJustCreated;
}
void freeList(Node* tail) {
    Node* temp;
    while (tail != NULL) {
        temp = tail->next;
        free(tail);
        tail = temp;
    }
}
void printList(Node* tail) {
    printf("LIST!\n");
    Node* temp;
    tail= tail->next;
    while (tail != NULL && tail->contentPointer != 0) {
        temp = tail->next;
        printf("Index: %d\tContentString: %s\n", tail->index,(const char*)tail->contentPointer);
        fflush(stdout);
        tail = temp;
    }
}
Node* getNode(Node* tail, int index) {
    Node* temp;
    tail= tail->next;
    while (tail != NULL && tail->contentPointer != 0) {
        temp = tail->next;
        if (temp->index == index)
        {
            return temp;
        }
        tail = temp;
    }
    return NULL;
}

/*int main () {
    Node* tail = createList();
    printList(tail);
    Node* head = tail;
    char buffer[32];
    for (int i = 0; i < 100; ++i)
    {
        _itoa(i, buffer, 10);
        head = addNode(head, strdup(buffer));
    }
    printList(tail);
    //get the pointer to the 44th node
    Node* getted = getNode(tail, 44);
    printf("Getted from index 44\nIndex: %d\tContentString: %s\n", getted->index,(const char*)getted->contentPointer);
    freeList(tail);
}*/
