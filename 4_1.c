#include <stdio.h>
#include <omp.h>

int fibonacci(int n);

int main() {
    int n = 10; // Change n to the desired Fibonacci number
    int result;

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    printf("F(%d) = %d\n", n, result);
    return 0;
}

int fibonacci(int n) {
    if (n <= 1)
        return n;

    int first = 0;
    int second = 1;
    int result = 0;

    #pragma omp task shared(result)
    {
        first = fibonacci(n - 1);
    }

    #pragma omp task shared(result)
    {
        second = fibonacci(n - 2);
    }

    #pragma omp taskwait

    result = first + second;

    return result;
}
