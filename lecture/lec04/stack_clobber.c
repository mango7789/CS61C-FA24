#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int *ptr () {
    int y;
    y = 3;
    return &y;
}

int main() {
    int *stackAddr, content;
    stackAddr = ptr();
    content = *stackAddr;
    printf("%d", content); /* 3 */
    content = *stackAddr;
    printf("%d", content); /*13451514 */
    return 0;
}