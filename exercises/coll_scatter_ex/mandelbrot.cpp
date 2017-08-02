#include <iostream>
#include <mpi.h>
#include <cmath>

// Global variables to store the rank of the process and the size
// of the communicator
int rank, size;

// Number of points on one side. The total number of points
// will be p_count*p_count.
constexpr int p_count = 512;

// Other global variables. We read them from the command line
// this will be handled by the script running on tech.io, don't
// mind this part.
// The cutoff variable indicates when we decide the series does not converge
// The other variable are just used to center the view and zoom level.
int cutoff;
double min_x, max_x, min_y, max_y, dx, dy;

// The modulus of a complex number
double modulus(double x, double y) {
  return sqrt(x*x + y*y);
} 

// Multiplying a complex number by itself
void self_mul(double &x, double &y) {
  double ox = x*x - y*y;
  double oy = x*y + y*x;
  x = ox;
  y = oy;
}

// Computation of the number of iterations on a set of points
// The result is stored in mset.
void compute_mandelbrot(double *points, int npts, int mset[]) {
  // For each point
  for (int i=0; i < npts; ++i) {
    double px, py;
    px = points[i*2];
    py = points[i*2+1];

    int iteration = 0;
    double zx = 0;
    double zy = 0;

    // We iterate until cutoff or modulus > 2
    while (iteration < cutoff) {
      self_mul(zx, zy);
      zx += px;
      zy += py;
      double mod = modulus(zx, zy);

      if (mod > 2.0f)
	break;

      iteration++;
    }

    // We store the number of iterations, and we use
    // a special value (-1) if we don't converge
    if (iteration == cutoff)
      mset[i] = -1;
    else
    mset[i] = iteration;
  }
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  // Reading the parameters on the command line
  min_x = std::stod(argv[1]);
  max_x = std::stod(argv[2]);
  min_y = std::stod(argv[3]);
  max_y = std::stod(argv[4]);
  dx = max_x - min_x;
  dy = max_y - min_y;
  cutoff = std::stoi(argv[5]);

  // Getting rank and size
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Initialisation of the points :
  // The process with rank 0 will hold all the points
  // The others will keep the variable poitns as a null pointer
  MPI_Barrier(MPI_COMM_WORLD);
  double *points = NULL;
  
  points = new double[p_count * p_count * 2];
  for (int yp=0; yp < p_count; ++yp) {
    double py = min_y + dy * yp / p_count;
    for (int xp=0; xp < p_count; ++xp) {
      double px = min_x + dx * xp / p_count;
      
      int lid = yp*p_count*2 + xp*2;
      points[lid]   = px;
      points[lid+1] = py;
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);

  // The number of points we hold
  int npts = p_count*p_count;
  
  // Computing the mandelbrot set.
  // This function is already coded and you don't have to worry about it
  int mset[npts];
  compute_mandelbrot(points, npts, mset);
  MPI_Barrier(MPI_COMM_WORLD);

  // Printing only one result that will be used to create the image
  if (rank==0) {
    for (int yp=0; yp < p_count; ++yp) {
      for (int xp=0; xp < p_count; ++xp)
	std::cout << mset[yp*p_count + xp] << " ";
      std::cout << std::endl;
    }
  }

  // Cleaning up the mess and exiting properly
  delete [] points;
  
  MPI_Finalize();
  return 0;
}
