#include <stdio.h>
#include <string.h>

void print_int_array(int arr[], int n);
void print_str_array(char *arr[], int n);

void swap(void *ptr1, void *ptr2, size_t nbytes) {
    char temp[nbytes];
    memcpy(temp, ptr1, nbytes);
    memcpy(ptr1, ptr2, nbytes);
    memcpy(ptr2, temp, nbytes);
}

void swap_ends(void *arr, size_t nelems, size_t nbytes) { 
    swap(arr, (char *)arr + (nelems - 1) * nbytes, nbytes); 
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    print_int_array(arr, n);
    swap_ends(arr, n, sizeof(arr[0]));
    print_int_array(arr, n);
    printf("\n");

    char *strs[] = {"Hi", "Hello", "Howdy"};
    n = sizeof(strs) / sizeof(strs[0]);
    print_str_array(strs, n);
    swap_ends(strs, n, sizeof(strs[0]));
    print_str_array(strs, n);

    return 0;
}

void print_int_array(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void print_str_array(char *arr[], int n) {
    for (int i = 0; i < n; i++) printf("%s ", arr[i]);
    printf("\n");
}