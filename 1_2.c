#include <stdio.h>
#include <omp.h>
int main() {
#pragma omp parallel
{
int thread_id = omp_get_thread_num();
printf("Executing THread Number : %d\n", thread_id);
}
return 0;
}