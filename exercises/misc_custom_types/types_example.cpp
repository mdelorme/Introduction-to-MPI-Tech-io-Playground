#include <iostream>
#include <cmath>
#include <mpi.h>

struct CustomData {
  int n_integers;
  int n_doubles;
  int* int_values;
  double* dbl_values;
};

int main(int argc, char **argv) {
  
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  CustomData data;

  if (rank == 0) {
    MPI_Status status;

    MPI_Probe(1, 0, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &data.n_integers);
    data.int_values = new int[data.n_integers];
    MPI_Recv(data.int_values, data.n_integers, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Probe(1, 1, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_DOUBLE, &data.n_doubles);
    data.dbl_values = new double[data.n_doubles];
    MPI_Recv(data.dbl_values, data.n_doubles, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "Process 0 has received " << data.n_integers << " ints and " << data.n_doubles << " doubles"
	      << std::endl;

    std::cout << "Values :" << std::endl;
    
    std::cout << " - ints = [";
    for (int i=0; i < data.n_integers; ++i)
      std::cout << data.int_values[i] << (i == data.n_integers-1 ? "]" : "; ");
    std::cout << std::endl;

    std::cout << " - doubles = [";
    for (int i=0; i < data.n_doubles; ++i)
      std::cout << data.dbl_values[i] << (i == data.n_doubles-1 ? "]" : "; ");
    std::cout << std::endl;
  }
  else {
    // Creating the dataset
    data.n_integers = 4;
    data.n_doubles  = 4;
    data.int_values = new int[data.n_integers];
    data.dbl_values = new double[data.n_doubles];

    for (int i=0; i < 4; ++i) {
      data.int_values[i] = (10+i)*i;
      data.dbl_values[i] = log(i+1.0);
    }

    // Sending the two tables, the number of elements will be probed
    MPI_Send(data.int_values, data.n_integers, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(data.dbl_values, data.n_doubles, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }

  // Freeing memory
  delete [] data.int_values;
  delete [] data.dbl_values;

  
  MPI_Finalize();
  
  return 0;
}
