# Hello World

Let's start diving in the code and program a simple Hello World running across multiple processes.

First of all, MPI must always be initialised and finalised. Both operations must be the first and last calls of your code, always. Now there is not much to say about these two operations, let's just say they setup the program. Although there is no strict obligation to call the initialisation as the first command of a program, let's read a bit of the MPICH implementation documentation that warns us :

``` The MPI standard does not say what a program can do before an MPI_INIT or after an MPI_FINALIZE. In the MPICH implementation, you should do as little as possible. In particular, avoid anything that changes the external state of the program, such as opening files, reading standard input or writing to standard output. ```

As a result and a matter of convention, these two commands are always called first and last in the program. The corresponding commands are `MPI_Init` and `MPI_Finalize`. `MPI_Init` always takes a reference to the command line arguments, while `MPI_Finalize` does not. Thus, in C++, their signatures are as follows :

```cpp
int MPI_Init(int *argc, char ***argv);
int MPI_Finalize();
```

If you remember, in the previous lesson we talked about *rank* and *size*. The way to obtain these, is to use the following calls :

```cpp
int size, rank;
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
```

Note the `MPI_COMM_WORLD`. We talked about it in the previous lesson, but let's just remember that `MPI_COMM_WORLD` indicates that the operation is done on the global communicator that encapsulates every single process of the current run. We will see later what communicators are and how to create them to create groups of processes. For the moment, we will stick with calling MPI on the `WORLD` communicator for this lesson and the next.

## Instructions
Now the first exercise will be to write a program which does the following steps :

* Initialises MPI.
* Reads the rank of the current process on `MPI_COMM_WORLD`.
* Prints `Hello world, from process #<RANK OF THE PROCESS`.
* Finalizes MPI and exits.

@[Hello World]({"stubs": ["intro_hello_world/hello_world.cpp"], "command": "bash intro_hello_world/hello_world.sh", "layout": "aside"})

## Notes on how to run this locally
If you try to compile this code locally, you might run into problems. There is a simple way to compile all MPI codes. When you install any implementation, such as OpenMPI or MPICH, wrapper compilers are provided. For instance, if you were to compile this code after having installed an OpenMPI distribution, you would have to replace the simple compiler line :

```bash
g++ -o hello_world hello_world.cpp
```

By :

```bash
mpicxx -o hello_world hello_world.cpp
```

There are three such wrappers to compile in the three languages mainly supported by MPI implementations : C, C++ and Fortran. The respective wrappers are : `mpicc`, `mpicxx` and `mpifort`. Note that these commands are simply wrappers, they will call compilers using environment variables. You can see the line that is actually executed when you use one of these compiler by using the `--show` command line argument. On a fairly standard Linux installation for instance, `mpicxx --show` will return something like :

```bash
g++ -I/usr/local/include -pthread -Wl,-rpath -Wl,/usr/local/lib -Wl,--enable-new-dtags -L/usr/local/lib -lmpi_cxx -lmpi
```

Once the program has been compiled, you can run it across multiple numbers of processes using the `mpirun` command. For instance, the exercise just above is run using the following commands (well, not only, but some additional parameters have been provided for tech.io) :

```bash
mpirun -np 4 ./hello_world
```

Note that `-np 4` indicates that the program will be run accross 4 processes. The list of parameters that you can provide to `mpirun` is long and complex. It is advised that, if you are interested in running such programs locally, you take a look at the official documentation of OpenMPI, or simply check `man mpirun` and `man mpicxx`.