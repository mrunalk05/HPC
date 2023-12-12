#include <mpi.h>
#include <stdio.h>


int main(int argc, char *argv[]) {
   MPI_Init(&argc, &argv);


   int rank;
   MPI_Group group;


   MPI_Comm_group(MPI_COMM_WORLD, &group);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);


   int group_size;
   MPI_Group_size(group, &group_size);


   printf("Rank: %d, Group Size: %d\n", rank, group_size);


   MPI_Finalize();
   return 0;
}


