#include <iostream>
#include <mpi.h>
#include <cmath>

#include "probing.cpp"

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int int_val;
  float float_val;
  int int_sum = 0;
  float float_sum = 0.0f;
  
  if (rank == 0) {  
    for (int i=0; i < 5; ++i) {
      MPI_Barrier(MPI_COMM_WORLD);
      probing_process(int_sum, float_sum);
    }
  }
  else if (rank == 1) {
    // Send 1
    MPI_Barrier(MPI_COMM_WORLD);
    int_val = 5;
    MPI_Send(&int_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    // Send 2
    MPI_Barrier(MPI_COMM_WORLD);

    // Send 3
    MPI_Barrier(MPI_COMM_WORLD);
    float_val = -12.0f;
    MPI_Send(&float_val, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);

    // Send 4
    MPI_Barrier(MPI_COMM_WORLD);
    int_val = -1;
    MPI_Send(&int_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

    // Send 5
    MPI_Barrier(MPI_COMM_WORLD);
  }
  else {
    // Send 1
    MPI_Barrier(MPI_COMM_WORLD);

    // Send 2
    MPI_Barrier(MPI_COMM_WORLD);
    float_val = 5.0f;
    MPI_Send(&float_val, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD);

    // Send 3
    MPI_Barrier(MPI_COMM_WORLD);

    // Send 4
    MPI_Barrier(MPI_COMM_WORLD);

    // Send 5
    MPI_Barrier(MPI_COMM_WORLD);
    int_val = 7;
    MPI_Send(&int_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  if (rank == 0) {
    if (int_sum != 11 || fabs(float_sum + 7.0f) > 1e-5) {
      std::cout << "TECHIO> success false" << std::endl;
    }
    else
      std::cout << "TECHIO> success true" << std::endl;
  }
  
  MPI_Finalize();
  
  return 0;
}
