#include <iostream>
#include <mpi.h>
#include "splitting.cpp"

bool check_validity() {
  if (world_rank == 0) {
    // Checking the sizes
    int s1, s2, s3;
    MPI_Comm_size(custom_comm1, &s1);
    MPI_Comm_size(custom_comm3, &s3);

    if (s1 != 4) {
      std::cerr << "ERROR : Custom comm 1 has not the right size !" << std::endl;
      return false;
    }

    if (s3 != 2) {
      std::cerr << "ERROR : Custom comm 3 has not the right size !" << std::endl;
      return false;
    }
  }

  if (world_rank == 4) {
    int s2;
    MPI_Comm_size(custom_comm2, &s2);
    if (s2 != 3) {
      std::cerr << "ERROR : Custom comm 2 has not the right size !" << std::endl;
      return false;
    }
  }

  if (world_rank < 4) {
    int value = (world_rank == 0 ? 100 : 0);
    MPI_Bcast(&value, 1, MPI_INT, 0, custom_comm1);
  }
  else if (world_rank < 7) {
    int value = (world_rank == 7 ? 75 : 0);
    MPI_Bcast(&value, 1, MPI_INT, 2, custom_comm2);
  }

  if (world_rank == 0 || world_rank == 4) {
    int value = (world_rank == 0 ? 10 : 0);
    MPI_Bcast(&value, 1, MPI_INT, 1, custom_comm3);
  }

  return true;
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  splitting();

  // Checks
  bool res = check_validity();

  MPI_Barrier(MPI_COMM_WORLD);

  // Exiting now
  MPI_Finalize();

  if (world_rank == 0)
    std::cout << "TECHIO> success " << (res ? "true" : "false") << std::endl;
  
  return 0;
}
