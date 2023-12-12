#include <stdio.h>
#include <omp.h>

#define VECTOR_SIZE 200

int main() {
    int A[VECTOR_SIZE], B[VECTOR_SIZE], C[VECTOR_SIZE];
    int chunk_sizes[] = {1, 5, 10, 20}; // Vary the chunk sizes here

    for (int i = 0; i < VECTOR_SIZE; i++) {
        A[i] = i;
        B[i] = VECTOR_SIZE - i;
    }

    printf("Vector A: ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    printf("Vector B: ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        printf("%d ", B[i]);
    }
    printf("\n");

    // Static Schedule
    printf("Static Schedule:\n");
    for (int chunk_index = 0; chunk_index < sizeof(chunk_sizes) / sizeof(chunk_sizes[0]); chunk_index++) {
        int chunk_size = chunk_sizes[chunk_index];

        double start_time = omp_get_wtime();

        #pragma omp parallel shared(A, B, C) 
        {
            #pragma omp for schedule(static, chunk_size)
            for (int i = 0; i < VECTOR_SIZE; i++) {
                C[i] = A[i] + B[i];
            }
        } // End of parallel region

        double end_time = omp_get_wtime();
        printf("Chunk Size %d, Execution Time: %f seconds\n", chunk_size, end_time - start_time);
    }

    // Dynamic Schedule
    printf("Dynamic Schedule:\n");
    for (int chunk_index = 0; chunk_index < sizeof(chunk_sizes) / sizeof(chunk_sizes[0]); chunk_index++) {
        int chunk_size = chunk_sizes[chunk_index];

        double start_time = omp_get_wtime();

        #pragma omp parallel shared(A, B, C) 
        {
            #pragma omp for schedule(dynamic, chunk_size)
            for (int i = 0; i < VECTOR_SIZE; i++) {
                C[i] = A[i] + B[i];
            }
        } // End of parallel region

        double end_time = omp_get_wtime();
        printf("Chunk Size %d, Execution Time: %f seconds\n", chunk_size, end_time - start_time);
    }

    printf("Vector C (Result): ");
    for (int i = 0; i < VECTOR_SIZE; i++) {
        printf("%d ", C[i]);
    }
    printf("\n");

    return 0;
}
