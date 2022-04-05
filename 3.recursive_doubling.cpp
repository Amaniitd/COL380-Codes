#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);

  int size, rank, buff_val;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    buff_val = 100;
  }

  for (int i = 1; i < size; i *= 2) {
    if (rank < i) {
      if (rank + i < size) {
        MPI_Send(&buff_val, 1, MPI_INT, rank + i, 0, MPI_COMM_WORLD);
        printf("%d send by the process %d.\n", buff_val, rank);
      }
    }
    else if (rank < 2 * i) {
      MPI_Recv(&buff_val, 1, MPI_INT, rank - i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%d recieved by the process %d.\n", buff_val, rank);
    }
  }

  MPI_Finalize();
}


















