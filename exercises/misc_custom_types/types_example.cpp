#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>

constexpr int DOUBLE_MAX = 10;
struct CustomData {
  int n_values;
  double values[DOUBLE_MAX];
};

int main(int argc, char **argv) {
  
  MPI_Init(&argc, &argv);

  int rank, size;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  constexpr int n_structure_per_process = 5; // M = 5

  // Random generator init
  srand(rank * 10);
  
  // Creating the dataset
  CustomData data[n_structure_per_process];

  // Generating the data
  for (int i=0; i < n_structure_per_process; ++i) {
    // Terrible way of generating random numbers, don't reproduce this at home
    data[i].n_values = rand() % DOUBLE_MAX + 1;
    for (int j=0; j < DOUBLE_MAX; ++j)
      data[i].values[j] = (j < data[i].n_values ? (double)rand() / (double)RAND_MAX : 0.0);
  }

  // Copying the data to two different arrays
  int int_send_buf[n_structure_per_process];
  double dbl_send_buf[n_structure_per_process * DOUBLE_MAX];

  for (int i=0; i < n_structure_per_process; ++i) {
    int_send_buf[i] = data[i].n_values;
    for (int j=0; j < data[i].n_values; ++j)
      dbl_send_buf[i*DOUBLE_MAX + j] = data[i].values[j];
  }

  // Gathering everything on process 0
  int *n_values = nullptr; 
  double *dbl_values = nullptr; 

  if (rank == 0) {
    n_values = new int[n_structure_per_process * size];
    dbl_values = new double[n_structure_per_process * size * DOUBLE_MAX];
  }
  
  MPI_Gather(int_send_buf, n_structure_per_process, MPI_INT,
	     n_values, n_structure_per_process, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Gather(dbl_send_buf, n_structure_per_process * DOUBLE_MAX, MPI_DOUBLE,
	     dbl_values, n_structure_per_process * DOUBLE_MAX, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    // Recopying the data and printing
    CustomData gathered_data[n_structure_per_process * size];
    memset(gathered_data, 0, n_structure_per_process * size * sizeof(CustomData));
    for (int i=0; i < size; ++i) {
      for (int j=0; j < n_structure_per_process; ++j) {
	int data_id = i * n_structure_per_process + j; // Linear index

	std::cout << "Data structure " << data_id << " : [";
	
	gathered_data[data_id].n_values = n_values[data_id];
	for (int k=0; k < n_values[data_id]; ++k) {
	  gathered_data[data_id].values[k] = dbl_values[i*n_structure_per_process*DOUBLE_MAX + j*DOUBLE_MAX + k];
	  std::cout << gathered_data[data_id].values[k] << (k == n_values[data_id]-1 ? "]" : "; ");
	}
	std::cout << std::endl;
      }
    }

    // And freeing the memory
    delete [] n_values;
    delete [] dbl_values;
  }
  
  
  MPI_Finalize();
  
  return 0;
}
