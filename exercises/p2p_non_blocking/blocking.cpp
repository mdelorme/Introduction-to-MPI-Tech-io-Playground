// This file is provided as an example of blocking scenario. Please don't modify it !
void play_blocking_scenario() {
  // Initialising buffer :
  for (int i=0; i < 10; ++i)
    buffer[i] = (rank == 0 ? i*i : 0);

  MPI_Barrier(MPI_COMM_WORLD);
  // Starting the chronometer
  double time = -MPI_Wtime(); // This command helps us measuring time. We will see more about it later !
  // Simulate working
  if (rank == 0) {
    sleep(3);
    std::cout << "0 " << time + MPI_Wtime() << std::endl;
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD);
    std::cout << "Send finished" << std::endl;
    sleep(6);
    std::cout << "0 " << time + MPI_Wtime() << std::endl;
    
    // Modifying the buffer for second step
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = -i;
    
    MPI_Send(buffer, buffer_count, MPI_INT, 1, 1, MPI_COMM_WORLD);
  }
  else {
    sleep(5);
    std::cout << "receiving" << std::endl;
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    print_buffer(time, 1, buffer, buffer_count); // This function prints the buffer for process 1
    sleep(3);
    MPI_Recv(buffer, buffer_count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    print_buffer(time, 2, buffer, buffer_count);
  }

  time += MPI_Wtime();
  
  // This line gives us the maximum time elapsed on each process.
  // We will see about reduction later on !
  double final_time;
  MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  if (rank == 0)
    std::cout << "Total time for blocking scenario : " << final_time << "s" << std::endl;
}
