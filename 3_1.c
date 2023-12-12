#include <stdio.h>
#include <time.h>
#include <omp.h>
int main() {
int size;
printf("Enter size of array = ");
scanf("%d", &size);
int arr1[size];
int arr2[size];
for (int i = 0; i < size; i++) {
arr1[i] = i;
arr2[i] = i;
}
int n = sizeof(arr1) / sizeof(arr1[0]);
clock_t st = clock();
// Ascending
for (int i = 0; i < n; i++) {
for (int j = i + 1; j < n; j++) {
if (arr1[i] > arr1[j]) {
    int temp = arr1[i];
arr1[i] = arr1[j];
arr1[j] = temp;
}
}
}
// Descending
for (int i = 0; i < n; i++) {
for (int j = i + 1; j < n; j++) {
if (arr2[i] < arr2[j]) {
int temp = arr2[i];
arr2[i] = arr2[j];
arr2[j] = temp;
}
}
}
double product = 0;
omp_set_num_threads(8);
#pragma omp parallel for schedule(static, 2) reduction(+:product)
for (int i = 0; i < n; i++) {
product += (double)arr1[i] * arr2[i];
int thread = omp_get_thread_num();
printf("\n%d. Thread = %d, Product = %f", i, thread, product);
}
clock_t et = clock();
double elapsed_time = (double)(et - st) / CLOCKS_PER_SEC;
double elapsed_milliseconds = elapsed_time * 1000;
printf("\nProduct: %f", product);
printf("\nTime taken: %f milliseconds", elapsed_milliseconds);
printf("\nTime taken: %f seconds\n", elapsed_time);
return 0;
}