#include <stdio.h>

int main() {
    int x = 3;

    void *ptr = &x;
    printf("%d\n", *ptr);

    void **doubleptr = &ptr;
    printf("%p\n", *doubleptr);
    printf("%ld\n", sizeof(*doubleptr));

    return 0;
}