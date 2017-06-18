#include <iostream>
#include <mpi.h>
#include <cstdlib>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Read the local value of the process
  // local_value will hold a specific int for process 0, and another for process 1
  int local_value;
  local_value = atoi(argv[1]);

  int other_value;
  if (rank == 0) {
    // Here, enter the code for the first process :
    // 1- Send the value to process 1 
    // 2- Receive the value from process 1 (in other_value)
    // 3- Print the sum of the two values on stdout 
    std::cout << "..." << std::endl;
  }
  else {
    // Here enter the code for the second process :
    // 1- Receive the value from process 0 (in other_value)
    // 2- Send the value to process 0
    // 3- Print the product of the two values on stdout
    std::cout << "..." << std::endl;
  }
  
  MPI_Finalize();
  
  return 0;
}
