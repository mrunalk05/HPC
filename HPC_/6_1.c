#include <stdio.h>
#include <omp.h>
#include <time.h>

void prefixSum(int *arr, int n) {
    int i, sum = 0;
// #pragma omp parallel for num_threads(4) 
    for (i = 0; i < n; i++) {
#pragma omp critical
        {
            sum += arr[i];
            arr[i] = sum;
        }
    }
}

int main() {
    #pragma omp parallel for num_threads(8) 
    double startTime = omp_get_wtime();
    int n = 1000;
    int arr[n];
    for (int i = 1; i <= n; i++) {
        arr[i - 1] = i;
    }
    prefixSum(arr, n);
  
    printf("data Size :");
    printf("%d ", n);
    printf("\n");
    printf("Threads: 8");
     printf("\n");
    double endTime = omp_get_wtime();
    printf("Execution time: %f", endTime - startTime);
     printf("\n");
    return 0;
}
