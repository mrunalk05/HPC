#include <omp.h>
#include<time.h>


#define N 4 // Matrix size (N x N)


void matrixVectorMult(int matrix[N][N], int vector[N], int result[N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        result[i] = 0; // Initialize the result for this row


        for (int j = 0; j < N; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}


int main() {
  double start=omp_get_wtime();
    int matrix[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };


    int vector[N] = {1, 2, 3, 4};
    int result[N];


    matrixVectorMult(matrix, vector, result);


    printf("Matrix-Vector Multiplication Result:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    double end=omp_get_wtime();


    printf("Execution time: %f", end-start);


    return 0;
}


