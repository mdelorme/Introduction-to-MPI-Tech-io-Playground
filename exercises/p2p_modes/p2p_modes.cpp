#include <iostream>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // We have two buffers, one big and one small
  constexpr int small_count = 50;
  constexpr int big_count   = 100000;
  int buff1[small_count];
  int buff2[big_count];

  // Waiting time, play with this value if you think the difference is due to the quantity of data to send
  constexpr int waiting_time = 5; // in seconds

  if (rank == 0) {
    // We initialize both buffers
    for (int i=0; i < big_count; ++i) {
      if (i < small_count)
	buff1[i] = i;
      buff2[i] = i;
    }

    // Synchronisation 1
    MPI_Barrier(MPI_COMM_WORLD);

    // We register the current time
    double time = -MPI_Wtime();

    // We send the buffer immediately
    MPI_Send(buff1, small_count, MPI_INT, 1, 0, MPI_COMM_WORLD);

    // We print the time it took us to complete this send
    std::cout << "Time elapsed to complete blocking send 1 : " << time + MPI_Wtime() << "s" << std::endl;

    // Synchronisation 2
    MPI_Barrier(MPI_COMM_WORLD);
    time = -MPI_Wtime();

    // We send the second buffer
    MPI_Send(buff2, big_count, MPI_INT, 1, 1, MPI_COMM_WORLD);

    // We print the time again
    std::cout << "Time elapsed to complete blocking send 2 : " << time + MPI_Wtime() << "s" << std::endl;
  }
  else {
    // Synchronisation 1
    MPI_Barrier(MPI_COMM_WORLD);
    sleep(waiting_time);

    // Receiving buffer 1
    MPI_Recv(buff1, small_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "Just received buffer 1" << std::endl;

    // Synchronisation 2
    MPI_Barrier(MPI_COMM_WORLD);
    sleep(waiting_time);

    // Receiving buffer 2
    MPI_Recv(buff2, big_count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "Just received buffer 2" << std::endl;
  }

  MPI_Finalize();
  
  return 0;
}
