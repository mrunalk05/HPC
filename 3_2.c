#include <stdio.h>
#include <omp.h>

int main() {
int dimension;
 printf("Enter dimension for 2D matrix = ");
 scanf("%d", &dimension);


int mp1[dimension][dimension], mp2[dimension][dimension];

 double start_time_parallel = omp_get_wtime();

 #pragma omp parallel for schedule(dynamic) num_threads(10000) collapse(2)
 for (int i = 0; i < dimension; i++) {
 for (int j = 0; j < dimension; j++) {
 mp1[i][j] = i + j;
 mp2[i][i] = i - j;
 }
 }
 int ans1[dimension][dimension];

#pragma omp parallel for schedule(dynamic) num_threads(1) collapse(2)
 for (int i = 0; i < dimension; i++) {
 for (int j = 0; j < dimension; j++) {
 ans1[i][j] = mp1[i][j] + mp2[i][j];
 }
 }
double end_time_parallel = omp_get_wtime();

 printf("\nParallel Method Time: %f seconds\n", (end_time_parallel - start_time_parallel));

return 0;
}