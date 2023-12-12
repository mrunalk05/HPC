#include <stdio.h>
#include <omp.h>
#include <time.h>

void prefixSum(int *arr, int n) {
    int i, sum = 0;
    for (i = 0; i < n; i++) {
        {
            sum += arr[i];
            arr[i] = sum;
        }
    }
}

int main() {
    int num_threads = 8;
    omp_set_num_threads(num_threads); 

    double startTime = omp_get_wtime();
    int n = 10;
    int arr[n];
    for (int i = 1; i <= n; i++) {
        arr[i - 1] = i;
    }
    prefixSum(arr, n);

    printf("data Size : %d\n", n);
    printf("Threads: %d\n", num_threads);
    double endTime = omp_get_wtime();
    printf("Execution time: %f\n", endTime - startTime);

    return 0;
}
