#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void mystery(short arr[], int len) {
    printf("%d ", len);
    printf("%ld\n", sizeof(arr));
}

int main() {
    short nums[] = {1, 2, 3, 99, 100};
    printf("%ld ", sizeof(nums));

    mystery(nums, sizeof(nums) / sizeof(short));

    return 0;
}