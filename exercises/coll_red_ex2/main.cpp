#include <iostream>
#include <mpi.h>
#include <cmath>

#include "barycentre.cpp"

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  constexpr int n_pts = 100;
  float points[n_pts][3];
  
  if (rank == 0) {
    for (int i=0; i < n_pts; ++i) {
      std::cin >> points[i][0] >> points[i][1] >> points[i][2];
      //      std::cout << points[i][0] << " " << points[i][1] << " " << points[i][2] << std::endl;
    }
  }

  
  int local_count = n_pts / size;
  std::cout << local_count << " " << local_count * size - n_pts << std::endl;
  float my_points[local_count][3];
  
  MPI_Scatter(points, local_count*3, MPI_FLOAT, my_points, local_count*3, MPI_FLOAT, 0, MPI_COMM_WORLD);

  compute(n_pts, local_count, my_points);

  MPI_Finalize();
  
  return 0;
}
