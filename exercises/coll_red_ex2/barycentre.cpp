void compute(int total_count, int my_count, float my_points[][3]) {
  // total_count is the total number of points
  // my_count is the number of points for this process
  // my_points is a float table of shape [my_count][3]

  // 1- Sum over all the points in local_sum
  float local_sum[3] = {0.0f, 0.0f, 0.0f};

  // 2- Reduce the sum of all the points on the variable barycentre 
  float barycentre[3];
  
  // 3- Divide every component of the barycentre by the number of points

  // For every point
  for (int i=0; i < my_count; ++i) {
    float dist = 0.0f;

    // 4- Compute the distance for every point
    
    // And printing the result
    std::cout << rank << " " << dist << std::endl;
  }
}
