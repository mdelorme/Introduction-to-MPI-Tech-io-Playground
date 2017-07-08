#include <iostream>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    // Process 0 is sending a random number (between 10 and 25) of integers to process 1
    int n_items = rand() % 16 + 10; // BAD way of doing random.
    std::cout << "Process 0, random count gives us " << n_items << " ints to send." << std::endl;

    // Allocation and initialisation of the buffer
    int *send_buf = new int[n_items];
    for (int i=0; i < n_items; ++i)
      send_buf[i] = i*i;

    std::cout << "Process 0, sending : ";
    for (int i=0; i < n_items; ++i)
      std::cout << send_buf[i] << " ";
    std::cout << std::endl;

    // Blocking send
    MPI_Send(send_buf, n_items, MPI_INT, 1, 0, MPI_COMM_WORLD);

    // Deallocation
    delete [] send_buf;
  }
  else {
    // Probing the reception of messages
    MPI_Status status;
    MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

    // From the probed status we get the number of elements to receive
    int n_items;
    MPI_Get_count(&status, MPI_INT, &n_items);

    std::cout << "Process 1, probing tells us message will have " << n_items << " ints." << std::endl;

    // Allocating and receiving
    int *recv_buf = new int[n_items];

    MPI_Recv(recv_buf, n_items, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "Process 1, buffer received : ";
    for (int i=0; i < n_items; ++i)
      std::cout << recv_buf[i] << " ";
    std::cout << std::endl;

    delete [] recv_buf;
  }

  MPI_Finalize();
  
  return 0;
}
