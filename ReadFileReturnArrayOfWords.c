#include <ctype.h>
#include <stdio.h>
#include "LinkedListImplementation.c"
#include <wctype.h>


int main() {

    int wc;

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
    }
}