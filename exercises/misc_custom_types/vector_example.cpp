#include <iostream>
#include <mpi.h>

struct Point {
  double x, y, z;
};

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Datatype dt_point;
  MPI_Type_contiguous(3, MPI_DOUBLE, &dt_point);
  MPI_Type_commit(&dt_point);
  
  constexpr int n_points = 10;
  Point data[n_points];

  // Process 0 sends the data
  if (rank == 0) {
    for (int i=0; i < n_points; ++i) {
      data[i].x = (double)i;
      data[i].y = (double)-i;
      data[i].z = (double) i * i;
    }

    MPI_Send(data, n_points, dt_point, 1, 0, MPI_COMM_WORLD);
  }
  else { // Process 1 receives
    MPI_Recv(data, n_points, dt_point, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Printing
    for (int i=0; i < n_points; ++i) {
      std::cout << "Point #" << i << " : (" << data[i].x << "; " << data[i].y << "; " << data[i].z << ")"
		<< std::endl;
    }
  }

  MPI_Finalize();
}
