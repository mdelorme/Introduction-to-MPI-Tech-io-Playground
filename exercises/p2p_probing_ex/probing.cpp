void probing_process(int &int_sum, float &float_sum) {
  MPI_Status status;
  
  // 1- Probe the incoming message

  // 2- Get the tag and the source
  int tag = [...];
  int source = [...];

  // Printing the message
  std::cout << "Received a message from process " << source << " with tag " << tag << std::endl;

  // 3- Add to int_sum or float_sum depending on the tag of the message
}
