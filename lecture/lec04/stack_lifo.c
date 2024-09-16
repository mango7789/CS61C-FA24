#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// function declarations
void a(int m);
void b(int n);
void c(int o);
void d(int p);

// function bodies
int main() {
    a(0);
    return 0;
}

void a(int m) {
    b(1);
}

void b(int n) {
    c(2);
}

void c(int o) {
    d(3);
}

void d(int p) {
    printf("return\n");
}