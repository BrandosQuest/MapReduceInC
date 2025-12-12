#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    void* contentPointer;
    Node* next;
    const Node* prev;
    uint32_t index;
};


Node* createList() {
    return calloc(1, sizeof(Node));
}

//returns the new head from the previous tail, if only one node, returns the head from the tail
Node* addNode(Node* head, void* contentPointer) {
    Node* nodeJustCreated = calloc(1, sizeof(Node));
    nodeJustCreated->contentPointer = contentPointer;
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
    Node* temp;
    while (tail != NULL) {
        temp = tail->next;
        printf("%s\n", (const char*)tail->contentPointer);
        fflush(stdout);
        tail = temp;
    }
}

int main () {
    Node* tail = createList();
    printList(tail);
    Node* head = tail;
    char buffer[35];

    for (int i = 0; i < 100; ++i)
    {
        printf("%s", _itoa(i, buffer, 10));
        head = addNode(head, _itoa(i, buffer, 10));
    }
    printList(tail);
    freeList(tail);
}
