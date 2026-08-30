#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int scalar_min_sum(int *a, int *b, int size) {
    int total_sum = 0;
    for (int i = 0; i < size; i++) {
        int min_value = a[i] < b[i] ? a[i] : b[i];  // Compute the minimum of a[i] and b[i]
        total_sum += min_value;  // Add it to the total sum
    }
    return total_sum;
}

int main() {
    int size = 10000000;  // 1 bln elements
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));

    // Initialize arrays with random values
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Measure the time for the scalar version
    clock_t start = clock();
    int sum = scalar_min_sum(a, b, size);
    clock_t end = clock();
    
    double scalar_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Total sum of minimums (scalar): %d\n", sum);
    printf("Time taken by scalar version: %f seconds\n", scalar_time);

    free(a);
    free(b);
    return 0;
}
