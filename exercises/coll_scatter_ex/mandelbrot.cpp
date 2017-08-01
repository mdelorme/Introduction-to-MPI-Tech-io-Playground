#include <iostream>
#include <mpi.h>
#include <cmath>

int rank, size;

constexpr int p_count = 512;
int cutoff;
double min_x, max_x, min_y, max_y, dx, dy;

double modulus(double x, double y) {
  return sqrt(x*x + y*y);
} 

void self_mul(double &x, double &y) {
  double ox = x*x - y*y;
  double oy = x*y + y*x;
  x = ox;
  y = oy;
}

void compute_mandelbrot(double *points, int npts, int mset[]) {
  for (int i=0; i < npts; ++i) {
    double px, py;
    px = points[i*2];
    py = points[i*2+1];

    int iteration = 0;
    double zx = 0;
    double zy = 0;

    while (iteration < cutoff) {
      self_mul(zx, zy);
      zx += px;
      zy += py;
      double mod = modulus(zx, zy);

      if (mod > 2.0f)
	break;

      iteration++;
    }

    if (iteration == cutoff)
      mset[i] = -1;
    else
    mset[i] = iteration;
  }
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  min_x = std::stod(argv[1]);
  max_x = std::stod(argv[2]);
  min_y = std::stod(argv[3]);
  max_y = std::stod(argv[4]);
  dx = max_x - min_x;
  dy = max_y - min_y;
  cutoff = std::stoi(argv[5]);
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (double(int(sqrt(size))) != sqrt(size)) {
    std::cout << "Error : Number of processes should be a square value" << std::endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
    return 0;
  }
  
  double *points = NULL;;
  int side_length = sqrt(size) * p_count;

  MPI_Barrier(MPI_COMM_WORLD);
  
  if (rank==0) {
    points = new double[p_count * p_count * size * 2];
    // Initialising the points to plot
    for (int yp=0; yp < side_length; ++yp) {
      double py = min_y + dy * yp / side_length;
      for (int xp=0; xp < side_length; ++xp) {
	double px = min_x + dx * xp / side_length;

	int lid = yp*side_length*2 + xp*2;
	points[lid]   = px;
	points[lid+1] = py;
      }
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);

  // Distributing the points over processes
  constexpr int npts = p_count*p_count;
  double my_points[npts*2];
  MPI_Scatter(points, npts*2, MPI_DOUBLE, my_points, npts*2, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);
  
  // Computing the mandelbrot set
  int mset[npts];
  compute_mandelbrot(my_points, npts, mset);

  MPI_Barrier(MPI_COMM_WORLD);
  
  // Gathering the results
  int* mset_tot;
  if (rank == 0)
    mset_tot = new int[npts*size];
  
  MPI_Gather(mset, npts, MPI_INT, mset_tot, npts, MPI_INT, 0, MPI_COMM_WORLD);
  
  if (rank == 0) {
    for (int yp=0; yp < side_length; ++yp) {
      for (int xp=0; xp < side_length; ++xp) {
	std::cout << mset_tot[yp*side_length + xp] << " ";
      }
      std::cout << std::endl;
    }
  }
  
  if (rank == 0) {
    delete [] points;
    delete [] mset_tot;
  }
  
  MPI_Finalize();
  return 0;
}
