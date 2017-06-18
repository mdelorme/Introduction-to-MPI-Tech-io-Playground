#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Initialising the data
  int buffer[5];

  if (rank==0) {
    // Storing some values in the buffer
    for (int i=0; i < 5; ++i)
      buffer[i] = i*i;
    
    for (int id_dest=1; id_dest < size; ++id_dest)
      MPI_Send(buffer, 5, MPI_INT, id_dest, 0, MPI_COMM_WORLD);
  }
  else {
    MPI_Recv(buffer, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  std::cout << "Process #" << rank << "; Buffer = (";
  for (int i=0; i < 5; ++i)
    std::cout << buffer[i] << (i < 4 ? " " : "");
  std::cout << ")" << std::endl;
  
  MPI_Finalize();
}
