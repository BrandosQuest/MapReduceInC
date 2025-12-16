#include <ctype.h>
#include <stdio.h>
typedef struct KeyVal KeyVal;
struct KeyVal {
    void* key;
    void* val;
};
#include "LinkedListImplementation.c"
#include <wctype.h>


int main() {
    Node* Tail1 = createList();
    Node* Tail1Ref = Tail1;
    Node* Head1 = Tail1;
    Node* Tail2 = createList();
    Node* Tail2Ref = Tail2;
    Node* Head2 = Tail2;

    for (int i = 0; i < 5; i++)
    {
        int* j=malloc(sizeof(int));
        if (j!=NULL)*j = i;

        Head1=addNode(Head1, j);
        Head2=addNode(Head2, j);
        if (Head1 == NULL || Head2 == NULL) free(j);
    }

    Node* temp;
    Tail1 = Tail1->next;
    while (Tail1 != NULL) {
        temp = Tail1->next;

        Tail2=Tail2Ref;

        Node* temp2;
        Tail2 = Tail2->next;
        while (Tail2 != NULL)
        {
            temp2 = Tail2->next;
            printf("Content of list 1, 2: %d, %d\n", *(int*)Tail1->contentPointer, *(int*)Tail2->contentPointer);
            Tail2 = temp2;
        }

        Tail1 = temp;
    }

    freeList(Tail1Ref);
    freeList(Tail2Ref);

    /*int wc;

    for (wc=0; wc <= 0xFF; wc++)
    {
        printf("%3d", wc);
        printf(" %#4x ", wc);
        printf("%3s", iswalnum(wc)  ? "AN" : " ");
        printf("%2s", iswalpha(wc)  ? "A"  : " ");//
        printf("%2s", iswblank(wc)  ? "B"  : " ");
        printf("%2s", iswcntrl(wc)  ? "C"  : " ");
        printf("%2s", iswdigit(wc)  ? "D"  : " ");//
        printf("%2s", iswgraph(wc)  ? "G"  : " ");
        printf("%2s", iswlower(wc)  ? "L"  : " ");
        printf(" %c", iswprint(wc)  ? wc   : ' ');
        printf("%3s", iswpunct(wc)  ? "PU" : " ");
        printf("%2s", iswspace(wc)  ? "S"  : " ");
        printf("%3s", iswprint(wc)  ? "PR" : " ");
        printf("%2s", iswupper(wc)  ? "U"  : " ");
        printf("%2s", iswxdigit(wc) ? "X"  : " ");

        putchar('\n');
    }*/

    /*Node* tail = createList();
    Node* head = tail;
    char [] arr

    for (int i = 0; i < 5; i++)
    {
        int* p = calloc(1, sizeof(int));
        head = addNode(head, p);
    }
    printListTrad(tail);
    freeList(tail);*/
}