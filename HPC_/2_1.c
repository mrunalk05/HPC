#include <stdio.h>
#include <omp.h>
#define VECTOR_SIZE 1000

int main() {
 float vector[VECTOR_SIZE];
 int scalar = 5;
 for (int i = 0; i < VECTOR_SIZE; i++) {
 vector[i] = i + 100.987;
 }

 double start_time_serial = omp_get_wtime();
 for (int i = 0; i < VECTOR_SIZE; i++) {
 vector[i] += scalar;
 }

 double end_time_serial = omp_get_wtime();
 printf("Serial Method Time: %f seconds\n", (end_time_serial - start_time_serial));

 for (int i = 0; i < VECTOR_SIZE; i++) {
 vector[i] = i + 100.987;
 }

 double start_time_parallel = omp_get_wtime();
 #pragma omp parallel for private(scalar) num_threads(1000)
 for (int i = 0; i < VECTOR_SIZE; i++) {
 vector[i] += scalar;
 }
double end_time_parallel = omp_get_wtime();
 printf("Parallel Method Time: %f seconds\n", (end_time_parallel - start_time_parallel));
 return 0;
}