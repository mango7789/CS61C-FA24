#include <stdio.h>

void print_array(int arr[], int n);

/* map function onto int array */
void mutate_map(int arr[], int n, int (*fp)(int)) {
    for (int i = 0; i < n; i++) arr[i] = (*fp)(arr[i]);
}

int multiply2(int x) { return 2 * x; }
int multiply10(int x) { return 10 * x; }

int main() {
    int arr[] = {3, 1, 4}, n = sizeof(arr) / sizeof(arr[0]);
    print_array(arr, n);  // prints int arr elements

    mutate_map(arr, n, &multiply2);
    print_array(arr, n);

    mutate_map(arr, n, &multiply10);
    print_array(arr, n);

    return 0;
}

/* helper functions defined */
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}