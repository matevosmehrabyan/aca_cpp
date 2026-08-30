#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include <time.h>

int avx_min_sum(int *a, int *b, int size) {
    int total_sum = 0;
    int i;

    // Initialize a 256-bit AVX register to accumulate the sum
    __m256i sum = _mm256_setzero_si256();

    for (i = 0; i < size; i += 8) {
        // Load 8 integers from each array into AVX registers
        __m256i vec_a = _mm256_loadu_si256((__m256i*)&a[i]);
        __m256i vec_b = _mm256_loadu_si256((__m256i*)&b[i]);

        // Compute the minimum of the corresponding integers in the two arrays
        __m256i min_vec = _mm256_min_epi32(vec_a, vec_b);

        // Add the results to the sum
        sum = _mm256_add_epi32(sum, min_vec);
    }

    // Extract the values from the AVX register into a temporary array
    int temp[8];
    _mm256_storeu_si256((__m256i*)temp, sum);

    // Sum up the values in the temporary array
    for (i = 0; i < 8; i++) {
        total_sum += temp[i];
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

    // Measure the time for the SIMD version
    clock_t start = clock();
    int sum = avx_min_sum(a, b, size);
    clock_t end = clock();
    
    double avx_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Total sum of minimums (AVX): %d\n", sum);
    printf("Time taken by SIMD (AVX) version: %f seconds\n", avx_time);

    free(a);
    free(b);
    return 0;
}
