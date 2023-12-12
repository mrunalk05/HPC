#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char *argv[])
{
printf("Printing Message Upto thread Count .... \n");
#pragma omp parallel num_threads (3)
printf("%s\n", "Hey there ..... ");
return 0 ;
}