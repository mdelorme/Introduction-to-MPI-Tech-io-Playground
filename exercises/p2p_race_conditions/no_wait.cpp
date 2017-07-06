#include <iostream>
#include <unistd.h>
#include <mpi.h>
 
int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
 
  MPI_Request request;
  MPI_Status  status;
  int         request_complete = 0;
 
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  constexpr int buffer_count = 10;
  int buffer[buffer_count];
 
  // Rank 0 sends, rank 1 receives
  if (rank == 0) {
    // Filling the buffer
    std::cout << "Process 0 is sending : ";
    for (int i=0; i < buffer_count; ++i) {
      buffer[i] = i*i;
      std::cout << buffer[i] << " ";
    }
    std::cout << std::endl;

    // Sending the data and waiting for 5 seconds
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
    sleep(5);
  }
  else {
    // Resetting the buffer
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = 0;

    // Receiving and sleeping for 5 seconds
    MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    sleep(5);

    // Printing the buffer received by process 1
    int ite = 0;
      std::cout << "Process 1 received : ";
      for (int i=0; i < buffer_count; ++i)
	std::cout << buffer[i] << " ";
      std::cout << std::endl;
  }
 
  MPI_Finalize();
}
