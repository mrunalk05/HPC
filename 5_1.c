// #include <iostream>
#include<stdio.h>
#include <omp.h>
// #include<bits/stdc++.h>
// using namespace std;
// const int N = 4; // Size of matrices

#define N 4
void sumLowerTriangularMatrices(int A[][N], int B[][N], int result[][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    int matrixA[N][N] = {
        {1, 0, 0, 0},
        {2, 3, 0, 0},
        {4, 5, 6, 0},
        {7, 8, 9, 10}
    };

    int matrixB[N][N] = {
        {10, 0, 0, 0},
        {9, 8, 0, 0},
        {7, 6, 5, 0},
        {4, 3, 2, 1}
    };

    int result[N][N];

    sumLowerTriangularMatrices(matrixA, matrixB, result);

    // Print the result matrix
    // cout << "Sum of lower triangular matrices:";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d",result[i][j]);
        }
        printf("\n");
        // cout << endl;
    }

    return 0;
}
