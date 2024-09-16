#include <stdio.h>
#include <string.h>

typedef struct {
    int x;
    char *s;
} mystruct;

void swap(void *ptr1, void *ptr2, size_t nbytes) {
    // 1. store a copy of data1 in temporary storage
    char temp[nbytes];
    memcpy(temp, ptr1, nbytes);

    // 2. copy data2 to location of data1
    memcpy(ptr1, ptr2, nbytes);

    // 3. copy data in temporary storage to location of data2
    memcpy(ptr2, temp, nbytes);
}

int main(int argc, char *argv[]) {
    // Example 1
    int x = 22, y = 61;
    printf("BEFORE: x = %d, y = %d\n", x, y);
    swap(&x, &y, sizeof(x));
    // swap(&x, &y, sizeof(short));  // what happens if we do this?
    printf(" AFTER: x = %d, y = %d\n", x, y);

    // Example 2
    char *str1 = "Hello", *str2 = "Goodbye";
    printf("BEFORE:    str1 %p: %s\n", str1, str1);
    printf("           str2 %p: %s\n", str2, str2);
    swap(&str1, &str2, sizeof(str1));
    printf(" AFTER:    str1 %p: %s\n", str1, str1);
    printf("           str2 %p: %s\n", str2, str2);

    // Example 3
    mystruct struct1 = {2, "Hello"};
    mystruct struct2 = {5, "Goodbye"};
    printf("BEFORE: struct1 x = %d, s = %s\n", struct1.x, struct1.s);
    printf("        struct2 x = %d, s = %s\n", struct2.x, struct2.s);
    swap(&struct1, &struct2, sizeof(mystruct));
    // swap(&struct1, &struct2, sizeof(int));  // what happens if we do this?
    printf(" AFTER: struct1 x = %d, s = %s\n", struct1.x, struct1.s);
    printf("        struct2 x = %d, s = %s\n", struct2.x, struct2.s);

    return 0;
}
