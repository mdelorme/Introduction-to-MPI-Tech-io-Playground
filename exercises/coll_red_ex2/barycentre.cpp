void compute(int total_count, int my_count, float my_points[][3]) {
  // total_count is the total number of points
  // my_count is the number of points for this process
  // my_points is a float table of shape [my_count][3]

  //  std::cout << my_points[0][0] << " " << my_points[0][1] << " " << my_points[0][2] << std::endl;

  // 1- Sum over all the points
  float local_sum[3] = {0.0f, 0.0f, 0.0f};
  for (int i=0; i < my_count; ++i) {
    for (int j=0; j < 3; ++j) {
      //  std::cout << local_sum[0] << " " << local_sum[1] << " " << local_sum[2] << std::endl;
      local_sum[j] += my_points[i][j];
    }
  }

  //  std::cout << local_sum[0] << " " << local_sum[1] << " " << local_sum[2] << std::endl;
  
  // 2- Reduction
  float barycentre[3];
  MPI_Allreduce(local_sum, barycentre, 3, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
  
  std::cout << barycentre[0] << " " << barycentre[1] << " " << barycentre[2] << std::endl;

  // 3- Dividing by the number of points
  for (int j=0; j < 3; ++j)
    barycentre[j] /= total_count;

  // 4- Computing the distance
  for (int i=0; i < my_count; ++i) {
    float dist = 0.0f;
    
    for (int j=0; j < 3; ++j) {
      float diff = barycentre[j] - my_points[i][j];
      dist += diff * diff;
    }
    dist = sqrt(dist);

    std::cout << dist << std::endl;
  }
}
